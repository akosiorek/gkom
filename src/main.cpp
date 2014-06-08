
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
#include "TexturedIndexedMesh.h"

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
#include "Texture.h"
#include "TexturedTechnique.h"
#include "typedefs.h"


//	Colours
glm::vec3 white(1, 1, 1);
glm::vec3 red(1, 0, 0);
glm::vec3 firebrick(178/255.0f, 34/255.0f, 34/255.0f);
glm::vec3 green(0, 1, 0);
glm::vec3 darkgreen(0, 100/255.f, 0);
glm::vec3 blue(0, 0, 1);
glm::vec3 skyblue(0, 0.75, 1);
glm::vec3 purple(1, 0, 1);
glm::vec3 black(0, 0, 0);
glm::vec3 gray(0.3, 0.3, 0.3);
glm::vec3 yellow(1, 1, 0);
glm::vec3 lightyellow(1, 1, .2);
glm::vec3 lightslaygray(119/255.f, 136/255.f, 153/255.f);

std::shared_ptr<SpaceShip> createShip(const std::vector<glm::vec3>& colours, bool b = false) {

	auto shipNode = std::make_shared<SpaceShip>(colours);
	shipNode->scale(4, 4, 4);
	if(b) shipNode->rotate(Axis::Y, 180);
	shipNode->translate(-53, 2, 50);
	// shipNode->rotate(Axis::Z, 45);
	shipNode->rotate(Axis::Y, 90);
	


	auto translate = std::make_shared<Trajectory>();
	translate->addMove(36, 360, MoveType::RotY);
	translate->addMove(-45, 45, MoveType::RotX);
	translate->addMove(40, 0, MoveType::TransZ);
	shipNode->addTrajectory(translate);

	auto rotateZ = std::make_shared<Trajectory>();
	rotateZ->addMove(1, 11, MoveType::Wait);
	rotateZ->addMove(20, 30, MoveType::Wait);
	rotateZ->addMove(20, 45, MoveType::RotX);
	rotateZ->addMove(40, 20, MoveType::Wait);
	rotateZ->addMove(90, 45, MoveType::RotX);
	rotateZ->addMove(40, 10, MoveType::Wait);
	rotateZ->addMove(-100, 55, MoveType::RotX);
	rotateZ->addMove(-180, 270, MoveType::RotY);
	rotateZ->addMove(20, 50, MoveType::Wait);
	rotateZ->addMove(180, 140, MoveType::RotY);
	rotateZ->addMove(20, 45, MoveType::Wait);
	rotateZ->addMove(360, 90, MoveType::RotZ);
	rotateZ->addMove(20, 20, MoveType::Wait);
	rotateZ->addMove(-360, 90, MoveType::RotZ);
	rotateZ->addMove(-100, 5, MoveType::RotX);

	shipNode->addTrajectory(rotateZ);

	auto rotate = std::make_shared<Trajectory>();
	rotate->addMove(1, 11, MoveType::Wait);
	rotate->addMove(40, 30, MoveType::Wait);
	rotate->addMove(80, 80, MoveType::RotY);
	rotate->addMove(400, 110, MoveType::RotZ);
	rotate->addMove(200, 10, MoveType::RotZ);
	rotate->addMove(100, 10, MoveType::RotZ);
	rotate->addMove(200, 10, MoveType::RotZ);
	rotate->addMove(400, 250, MoveType::RotZ);
	shipNode->addTrajectory(rotate);

	return shipNode;
}

void setupCameraMovement(CameraPtr camera) {

	auto rotate = std::make_shared<Trajectory>();
	rotate->addMove(1, 10, MoveType::Wait);
	rotate->addMove(200, 200, MoveType::TransX);
	rotate->addMove(10, 135, MoveType::RotY);
	// rotate->addMove(-360, 210, MoveType::RotY);
	// rotate->addMove(10, 40, MoveType::Wait);
	// rotate->addMove(30, 90, MoveType::RotY);
	// rotate->addMove(-50, 90, MoveType::RotY);
	// rotate->addMove(-0, 60, MoveType::RotY);
	// rotate->addMove(-180, 120, MoveType::RotY);
	camera->addTrajectory(rotate);

	auto rotate2 = std::make_shared<Trajectory>();
	rotate2->addMove(1, 10, MoveType::Wait);
	rotate2->addMove(100, 100, MoveType::TransY);
	// rotate2->addMove(10, 45, MoveType::RotX);
	rotate2->addMove(-20, 90, MoveType::TransY);
	camera->addTrajectory(rotate2);


	auto translate = std::make_shared<Trajectory>();
	translate->addMove(1, 10, MoveType::Wait);
	translate->addMove(200, 200, MoveType::TransZ);
	translate->addMove(-20, 90, MoveType::TransZ);
	// translate->addMove(10, 55, MoveType::Wait);
	// translate->addMove(-20, 90, MoveType::TransY);
// 	// translate->addMove(-50, 50, MoveType::TransX);
// 	translate->addMove(-10, 100, MoveType::TransZ);
	camera->addTrajectory(translate);
}

int main(int argc, char** argv) {

	srand (time(NULL));

//	Camera setup
	CameraPtr camera = std::make_shared<PerspectiveCamera>();
	camera->setClipping(0.5f, 1000.f);
	camera->translate(-212,  20, 250);
	// camera->pointAt(-212, 40, 212);
	
	// camera->rotate(Axis::X, 45);
	setupCameraMovement(camera);

//	Renderer setup
	RendererPtr renderer(new RendererOGL(1920, 1080));
	renderer->init();
	renderer->setCamera(camera);
	// Wire frame rendering
	// glPolygonMode(GL_FRONT, GL_LINE);

	MeshConfig::UNIFORM_COLOR_PROGRAM = Utils::createProgram({
		Utils::loadShader(GL_VERTEX_SHADER, "light_vs.glsl"),
		Utils::loadShader(GL_FRAGMENT_SHADER, "colours3_fs.glsl")
	});

//	Mesh setup
	std::unique_ptr<PlaneGenerator> planeGenerator(new PlaneGenerator());
	planeGenerator->generate(100, 100, 80);

//	Textured floor
	auto floorMesh = std::make_shared<TexturedIndexedMesh>(
		planeGenerator->getVertices(),
		planeGenerator->getNormals(),
		planeGenerator->getTextureCoords(),
		planeGenerator->getIndices(),
		GL_TRIANGLE_STRIP
	);
	std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>(GL_TEXTURE_2D, "../textures/sand2.png");
	// std::shared_ptr<Texture> floorTexture = std::make_shared<Texture>(GL_TEXTURE_2D, "../textures/moon.png");
	floorTexture->load();
	std::shared_ptr<TexturedTechnique> texturedTechnique = std::make_shared<TexturedTechnique>();
	texturedTechnique->enable();
	texturedTechnique->setTextureUnit(0);
	texturedTechnique->setAmbientIntensity(glm::vec4(.2f, .2f, 0.2f, 1.f));
	texturedTechnique->setDiffuseIntensity(glm::vec4(1.f, 1.f, 1.f, 1.f));
	texturedTechnique->setDiffuseDir(glm::vec3(1.0f, -.5f, -1.f));
	floorMesh->setTechnique(texturedTechnique);
	floorMesh->setTexture(floorTexture);

//	Root node
	NodePtr rootNode = std::make_shared<Node>();

//	Skybox
	auto skyboxMesh = std::make_shared<SkyboxMesh>("../textures/skybox/", 
		std::vector<std::string>({"+x.png", "-x.png", "+y.png", "-y.png", "+z.png", "-z.png"}));
	auto skyboxNode = std::make_shared<Node>(skyboxMesh);
	skyboxNode->scale(100, 100, 100);
	rootNode->addChild(skyboxNode);

//	Floor node
	NodePtr floorNode = std::make_shared<Node>(floorMesh);
	floorNode->translate(-500, -20, -500);
	floorNode->scale(10, 10, 10);
	rootNode->addChild(floorNode);

//	Ship
	// rootNode->addChild(std::make_shared<SpaceShip>(std::vector<glm::vec3>({lightyellow, skyblue})));
	auto shipA = createShip({darkgreen, firebrick});
	auto shipB = createShip({lightyellow, skyblue}, true);

	rootNode->addChild(shipA);
	rootNode->addChild(shipB);


// Rotating nodes
	NodePtr rotatingNode = std::make_shared<Node>();
	rotatingNode->translate(0, 2, 0);
	rootNode->addChild(rotatingNode);

//	Ambient light
	Utils::setAmbientLightIntensity(glm::vec4(.2f, .2f, 0.2f, 1.f));
	Utils::setDiffuseLightIntensity(glm::vec4(.9f, .9f, 0.9f, 1.f));
	Utils::setDiffuseLightDir(glm::vec3(1.0f, -.5f, -1.f));

//	Movement
	float speed = 2.0f;
	long counter = 0;

	double totalTime = 0;
	std::vector<double> timeIntervals = {120, 140, 220, 260};
	for(int i = 0; i < timeIntervals.size(); ++i) {

		timeIntervals[i] /= speed * 10;
	}

	while(!renderer->shouldClose()) {

		double elapsedTime = Utils::elapsedSinceLastFrame();
		double augmentedTime = speed * elapsedTime;

		camera->update(augmentedTime);
		renderer->clearScreen();
		renderer->render(rootNode, augmentedTime);

		counter++;
		for(int i = 0; i < timeIntervals.size()/2; ++i) {
			if(totalTime > timeIntervals[i * 2] && totalTime < timeIntervals[i * 2 + 1]) {
				if(counter % 5 == 0) {
					rootNode->addChild(shipA->shoot());
					rootNode->addChild(shipB->shoot());
				}
			}
		}
		totalTime += elapsedTime;
	}
}
