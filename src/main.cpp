
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

#include "typedefs.h"

#include <iostream>


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
		Utils::loadShader(GL_VERTEX_SHADER, "ambient_is_diffuse_vs.glsl"),
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
	MeshPtr floorMesh = std::make_shared<UniformColourMesh>(
			planeGenerator->getVertices(),
			colour,
			planeGenerator->getIndices(),
			GL_TRIANGLE_STRIP
	);
	floorMesh->setNormals(planeGenerator->getNormals());

	//simple plane
	std::vector<float> planeGeom = Utils::loadVertexData("plane.vert");
	std::vector<unsigned> planeIndices;
	for(int i = 0; i < planeGeom.size(); ++i) {
		planeIndices.push_back(i);
	}
	std::cout << planeGeom.size() << std::endl;
	std::vector<float> white = {1, 1, 1};

	MeshPtr planeMesh = std::make_shared<UniformColourMesh>(
			planeGeom,
			white,
			planeIndices
	);
	planeMesh->setNormals(Utils::loadVertexData("plane.norm"));



	NodePtr boxNode = std::make_shared<Node>();
	NodePtr upBoxNode = std::make_shared<Node>(planeMesh);
	NodePtr rightBoxNode = std::make_shared<Node>(planeMesh);
	NodePtr fronBoxNode = std::make_shared<Node>(planeMesh);
	NodePtr downBoxNode = std::make_shared<Node>(planeMesh);
	NodePtr leftBoxNode = std::make_shared<Node>(planeMesh);
	NodePtr backBoxNode = std::make_shared<Node>(planeMesh);

	upBoxNode->translate(0, 1);

	rightBoxNode->translate(1);
	rightBoxNode->rotate(Axis::Z, -90);
	fronBoxNode->translate(0, 0, 1);
	fronBoxNode->rotate(Axis::X, 90);
	downBoxNode->translate(0, -1);
	downBoxNode->rotate(Axis::Y, 180);
	leftBoxNode->translate(-1);
	leftBoxNode->rotate(Axis::Z, 90);
	backBoxNode->translate(0, 0, -1);
	backBoxNode->rotate(Axis::X, 90);
//
	boxNode->addChild(upBoxNode);
	boxNode->addChild(rightBoxNode);
	boxNode->addChild(fronBoxNode);
	boxNode->addChild(downBoxNode);
	boxNode->addChild(leftBoxNode);
	boxNode->addChild(backBoxNode);


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

//	Floor node
	NodePtr floorNode = std::make_shared<Node>(floorMesh);

	floorNode->translate(-50, -3, -50);

//	Root node
	NodePtr rootNode = std::make_shared<Node>();
	rootNode->addChild(floorNode);
	rootNode->addChild(rotatingNode);
	rotatingNode->addChild(boxNode);

//	Ambient light
	Utils::setAmbientLight(glm::vec4(1.f, 1.f, 1.f, 1.0f));


//	Movement
	float speed = 100.0f;


	while(!renderer->shouldClose()) {

		float shouldRotate = Utils::elapsedSinceLastFrame() * speed;

		rotatingNode->rotate(Axis::Z, shouldRotate);
		rightNode->rotate(Axis::Z, -shouldRotate);
		centerNode->rotate(Axis::Z, -shouldRotate);
		leftNode->rotate(Axis::Z, -shouldRotate);
		renderer->clearScreen();
		renderer->render(rootNode);
	}
}
