
//	Camera
#include "ICamera.h"
#include "PerspectiveCamera.h"

//	Mesh
#include "IMesh.h"
#include "MeshConfig.h"
#include "UniformColouredMesh.h"

//	Renderer
#include "IRenderer.h"
#include "RendererOGL.h"

//	Others
#include "Node.h"
#include "Utils.h"
#include "PlaneGenerator.h"
#include "NormalGenerator.h"
#include "Box.h"
#include "Trajectory.h"
#include "PolyhedronGenerator.h"
#include "SpaceShip.h"

#include "typedefs.h"

#include <iostream>
#include <fstream>

template<typename T>
void dumpVec(const std::vector<T>& vec, const std::string& logfile) {

	std::ofstream of(logfile);
	for(int i = 0; i < vec.size(); ++i) {
		of << vec[i] << " ";
		if((i+1) % 3 == 0)
			of << std::endl;
	}
}

std::vector<float> white = {1, 1, 1};
std::vector<float> red = {1, 0, 0};
std::vector<float> green = {0, 1, 0};
std::vector<float> blue = {0, 0, 1};
std::vector<float> purple = {1, 0, 1};
std::vector<float> black = {0, 0, 0};
std::vector<float> gray = {0.3, 0.3, 0.3};


int main(int argc, char** argv) {

	srand (time(NULL));

//	Camera setup
	CameraPtr camera = std::make_shared<PerspectiveCamera>();
	camera->setClipping(0.5f, 100.f);
	// camera->rotate(Axis::Y, -135);
	camera->translate(3, 10, -10);
	// camera->pointAt(0, 0, 0);
	// camera->rotate(Axis::X, -45);
	// camera->rotate(Axis::, -45);

//	Renderer setup
	RendererPtr renderer(new RendererOGL());
	renderer->init();
	renderer->setCamera(camera);
//	Wire frame rendering
//	glPolygonMode(GL_FRONT, GL_LINE);

	MeshConfig::UNIFORM_COLOR_PROGRAM = Utils::createProgram({
		Utils::loadShader(GL_VERTEX_SHADER, "ambient_is_diffuse_vs.glsl"),
		Utils::loadShader(GL_FRAGMENT_SHADER, "colours3_fs.glsl")
	});


//	Mesh setup
	std::unique_ptr<PlaneGenerator> planeGenerator(new PlaneGenerator());

	planeGenerator->generate(100, 100, 80);
	MeshPtr floorMesh = std::make_shared<UniformColourMesh>(
			planeGenerator->getVertices(),
			planeGenerator->getNormals(),
			blue,
			planeGenerator->getIndices(),
			GL_TRIANGLE_STRIP
	);

// Rotating nodes
	NodePtr rotatingNode = std::make_shared<Node>();
	rotatingNode->translate(0, 2, 0);

//	Floor node
	NodePtr floorNode = std::make_shared<Node>(floorMesh);

	floorNode->translate(-50, -3, -50);

// Ship
	// NodePtr shipNode = createSpaceShip();
	auto shipNode = std::make_shared<SpaceShip>();
	// shipNode->translate(4);
	shipNode->rotate(Axis::Y, 90);

//	Root node
	NodePtr rootNode = std::make_shared<Node>();
	rootNode->addChild(floorNode);
	rootNode->addChild(rotatingNode);
	rotatingNode->addChild(shipNode);
//	rootNode->addChild(shipNode);

//	Ambient light
	Utils::setAmbientLight(glm::vec4(.3f, .3f, 0.3f, 1.0f));

//	Movement
	float speed = 100.0f;

	while(!renderer->shouldClose()) {

		double elapsedTime = Utils::elapsedSinceLastFrame();
		float shouldRotate = elapsedTime * speed;

		rotatingNode->rotate(Axis::Y, shouldRotate);
		renderer->clearScreen();
		renderer->render(rootNode, elapsedTime);
	}
}