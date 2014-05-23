

#include "IRenderer.h"
#include "ICamera.h"

#include "RendererOGL.h"
#include "PerspectiveCamera.h"
#include "Node.h"
#include "Mesh.h"

#include "Utils.h"

#include <iostream>
#include <memory>

typedef std::unique_ptr<IRenderer> RendererPtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Node> NodePtr;
typedef std::shared_ptr<ICamera> CameraPtr;

int main(int argc, char** argv) {

	CameraPtr camera = std::make_shared<PerspectiveCamera>();

	RendererPtr renderer(new RendererOGL());
	renderer->init();
	renderer->setCamera(camera);

	std::vector<GLuint> shaders = {
			Utils::loadShader(GL_VERTEX_SHADER, "matrix_vs.glsl"),
			Utils::loadShader(GL_FRAGMENT_SHADER, "colours_fs.glsl")
	};

	GLuint program = Utils::createProgram(shaders);
	std::string viewName = "perspectiveMatrix";
	auto colour = Utils::loadVertexData("matrix.col");
	auto geom = Utils::loadVertexData("matrix.vert");
	MeshPtr mesh = std::make_shared<Mesh>(geom, colour);
	mesh->setProgram(program);
	mesh->setViewName(viewName);

	NodePtr rootNode = std::make_shared<Node>();

	NodePtr leftNode = std::make_shared<Node>(mesh);
	leftNode->translate(-0.75f, 0.3f, .0);

	NodePtr centerNode = std::make_shared<Node>(mesh);
	centerNode->translate(.0f, .5f, .0f);

	NodePtr rightNode = std::make_shared<Node>(mesh);
	rightNode->translate(0.75f, -.3f, .0f);

	rootNode->addChild(leftNode);
	rootNode->addChild(centerNode);
	rootNode->addChild(rightNode);

	float speed = 100.0f;
	float rotated = .0f;

	while(!renderer->shouldClose()) {

		float shouldRotate = Utils::elapsedSinceLastFrame() * speed;
		rotated += shouldRotate;
		if(rotated >= 180.f || rotated <= -180.0f) {
			speed *= -1;
		}
		rootNode->roate(Axis::Z, shouldRotate);
		rightNode->roate(Axis::Z, -shouldRotate);
		centerNode->roate(Axis::Z, -shouldRotate);
		leftNode->roate(Axis::Z, -shouldRotate);
		renderer->clearScreen();
		renderer->render(rootNode);
	}
}
