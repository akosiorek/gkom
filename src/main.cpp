
//	Camera
#include "ICamera.h"
#include "PerspectiveCamera.h"

//	Renderer
#include "IRenderer.h"
#include "RendererOGL.h"

//	Mesh
#include "IMesh.h"
#include "MeshConfig.h"
#include "BasicMesh.h"
#include "IndexedMesh.h"
#include "SkyboxMesh.h"

//	Node
#include "Node.h"
#include "Box.h"
#include "SpaceShip.h"

//	Generators
#include "PlaneGenerator.h"
#include "NormalGenerator.h"
#include "PolyhedronGenerator.h"

//	Utilities
#include "Utils.h"
#include "Trajectory.h"

#include "typedefs.h"


//	Colours
glm::vec3 white(1, 1, 1);
glm::vec3 red(1, 0, 0);
glm::vec3 green(0, 1, 0);
glm::vec3 blue(0, 0, 1);
glm::vec3 purple(1, 0, 1);
glm::vec3 black(0, 0, 0);
glm::vec3 gray(0.3, 0.3, 0.3);


int main(int argc, char** argv) {

	srand (time(NULL));

//	Camera setup
	CameraPtr camera = std::make_shared<PerspectiveCamera>();
	camera->setClipping(0.5f, 500.f);
	camera->translate(3, 10, -10);
	auto cameraTrajectory = std::make_shared<Trajectory>();
	cameraTrajectory->addMove(20, 0, MoveType::RotY);
	camera->addTrajectory(cameraTrajectory);

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
	MeshPtr floorMesh = std::make_shared<IndexedMesh>(
			planeGenerator->getVertices(),
			planeGenerator->getNormals(),
			planeGenerator->getIndices(),
			blue,
			GL_TRIANGLE_STRIP
	);

//	Root node
	NodePtr rootNode = std::make_shared<Node>();

//	Skybox
	auto skyboxMesh = std::make_shared<SkyboxMesh>("../textures/skybox/", 
		std::vector<std::string>({"posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"}));
	auto skyboxNode = std::make_shared<Node>(skyboxMesh);
	rootNode->addChild(skyboxNode);

//	Floor node
	NodePtr floorNode = std::make_shared<Node>(floorMesh);
	floorNode->translate(-500, -10, -500);
	floorNode->scale(10, 5, 10);
	rootNode->addChild(floorNode);

//	Ship
	auto shipNode = std::make_shared<SpaceShip>();
	shipNode->rotate(Axis::Y, 90);
//	rootNode->addChild(shipNode);

// Rotating nodes
	NodePtr rotatingNode = std::make_shared<Node>();
	rotatingNode->translate(0, 2, 0);
	rootNode->addChild(rotatingNode);
	rotatingNode->addChild(shipNode);

//	Ambient light
	Utils::setAmbientLight(glm::vec4(.3f, .3f, 0.3f, 1.0f));

//	Movement
	float speed = 100.0f;

	while(!renderer->shouldClose()) {

		double elapsedTime = Utils::elapsedSinceLastFrame();
		float shouldRotate = elapsedTime * speed;

		camera->update(elapsedTime);
		rotatingNode->rotate(Axis::Y, shouldRotate);
		renderer->clearScreen();
		renderer->render(rootNode, elapsedTime);
	}
}
