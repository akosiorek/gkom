
//	Camera
#include "ICamera.h"
#include "PerspectiveCamera.h"

//	Mesh
#include "IMesh.h"
#include "MeshConfig.h"
#include "ColouredVertMesh.h"
#include "UniformColouredMesh.h"

//	Renderer
#include "IRenderer.h"
#include "RendererOGL.h"

//	Others
#include "Node.h"
#include "Utils.h"
#include "PlaneGenerator.h"

#include <iostream>
#include <memory>

typedef std::unique_ptr<IRenderer> RendererPtr;
typedef std::shared_ptr<IMesh> MeshPtr;
typedef std::shared_ptr<Node> NodePtr;
typedef std::shared_ptr<ICamera> CameraPtr;


int main(int argc, char** argv) {

	srand (time(NULL));

//	Camera setup
	CameraPtr camera = std::make_shared<PerspectiveCamera>();
	camera->setClipping(0.5f, 100.f);

	camera->translate(3, 4, -1);
	camera->rotate(Axis::X, -45);

//	Renderer setup
	RendererPtr renderer(new RendererOGL());
	renderer->init();
	renderer->setCamera(camera);
//	Wire frame rendering
//	glPolygonMode(GL_FRONT, GL_LINE);

//	Program setup
	MeshConfig::COLORED_VERT_PROGRAM = Utils::createProgram({
		Utils::loadShader(GL_VERTEX_SHADER, "matrix_vs.glsl"),
		Utils::loadShader(GL_FRAGMENT_SHADER, "colours_fs.glsl")
	});

	MeshConfig::UNIFORM_COLOR_PROGRAM = Utils::createProgram({
		Utils::loadShader(GL_VERTEX_SHADER, "unif_colour_matrix_vs.glsl"),
//		Utils::loadShader(GL_VERTEX_SHADER, "light_vs.glsl"),
		Utils::loadShader(GL_FRAGMENT_SHADER, "colours3_fs.glsl")
	});


//	Mesh setup
	std::unique_ptr<PlaneGenerator> planeGenerator(new PlaneGenerator());

	std::vector<float> cuboidGeom = Utils::loadVertexData("matrix3.vert");
	std::vector<unsigned> cuboidIndices;
	for(int i = 0; i < cuboidGeom.size(); ++i) {
		cuboidIndices.push_back(i);
	}

	MeshPtr cuboidMesh = std::make_shared<ColouredVertMesh>(
			cuboidGeom,
			Utils::loadVertexData("matrix3.col"),
			cuboidIndices
	);

	std::vector<float> colour = {.3f, .3f, 1.0f};


	planeGenerator->generate(100, 100, 80);
	MeshPtr planeMesh = std::make_shared<UniformColouredMesh>(
			planeGenerator->getVertices(),
			colour,
			planeGenerator->getIndices(),
			GL_TRIANGLE_STRIP
//			planeGenerator->getNormals()
	);
	planeMesh->setNormals(planeGenerator->getNormals());


// Rotating nodes
	NodePtr rotatingNode = std::make_shared<Node>();
	rotatingNode->translate(0, 2, 0);

	NodePtr leftNode = std::make_shared<Node>(cuboidMesh);
	leftNode->translate(-0.75f, 0.3f, .0);

	NodePtr centerNode = std::make_shared<Node>(cuboidMesh);
	centerNode->translate(.0f, .5f, .0f);

	NodePtr rightNode = std::make_shared<Node>(cuboidMesh);
	rightNode->translate(0.75f, -.3f, .0f);

	rotatingNode->addChild(leftNode);
	rotatingNode->addChild(centerNode);
	rotatingNode->addChild(rightNode);

//	Plane node
	NodePtr planeNode = std::make_shared<Node>(planeMesh);

	planeNode->translate(-50, 0, -50);
//	planeNode->scale(3, 3, 3);

//	Root node
	NodePtr rootNode = std::make_shared<Node>();
	rootNode->addChild(planeNode);
	rootNode->addChild(rotatingNode);

//	Ambient light
	Utils::setAmbientLight(glm::vec4(3.f, 1.f, 1.f, 1.0f));


//	Movement
	float speed = 100.0f;
	float rotated = .0f;


	while(!renderer->shouldClose()) {

		float shouldRotate = Utils::elapsedSinceLastFrame() * speed;
//		rotated += shouldRotate;
//		if(rotated >= 180.f || rotated <= -180.0f) {
//			speed *= -1;
//		}

		rotatingNode->rotate(Axis::Z, shouldRotate);
		rightNode->rotate(Axis::Z, -shouldRotate);
		centerNode->rotate(Axis::Z, -shouldRotate);
		leftNode->rotate(Axis::Z, -shouldRotate);
		renderer->clearScreen();
		renderer->render(rootNode);
	}
}
