/*
 * RendererOGL.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "RendererOGL.h"
#include "ICamera.h"

#include <stdexcept>

RendererOGL::RendererOGL(int width, int height, std::string name)
	: width_(width), height_(height), name_(name) {}

RendererOGL::~RendererOGL() {
	shutdown();
}

void RendererOGL::init() {

	if (!glfwInit()) {
		throw new std::runtime_error("could not start GLFW3");
	}

	window_ = glfwCreateWindow(width_, height_, name_.c_str(), NULL, NULL);
	if (!window_) {
		throw new std::runtime_error("could not open window with GLFW3");
	}
	glfwMakeContextCurrent(window_);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

	// enable face culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
}

void RendererOGL::shutdown() {
	glfwTerminate();
}

void RendererOGL::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererOGL::traverse(NodePtr node, const glm::mat4& current) {

}

void RendererOGL::render(NodePtr node) {

	traverse(node, camera_->getTransform());

	glfwSwapBuffers(window_);
	glfwPollEvents();
	if(glfwWindowShouldClose(window_)) {
		shouldClose_ = true;
	}
}

void RendererOGL::setCamera(CameraPtr camera) {

}

auto RendererOGL::getCamera() -> CameraPtr {

}

bool RendererOGL::shouldClose() {

	return shouldClose_;
}
