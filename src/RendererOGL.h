/*
 * RendererOGL.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef RENDEREROGL_H_
#define RENDEREROGL_H_

#include "IRenderer.h"

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class RendererOGL : public IRenderer {
public:
	RendererOGL(int width = 1024, int height = 768, std::string name = "OpenGL Renderer");
	virtual ~RendererOGL();

	virtual void render(NodePtr node) override;
	virtual void clearScreen() override;
	virtual void init() override;
	virtual void shutdown() override;

	virtual void setCamera(CameraPtr camera) override;
	virtual CameraPtr getCamera() override;

	virtual bool shouldClose() override;

private:
	void traverse(NodePtr node, const glm::mat4& current);

	int width_;
	int height_;
	std::string name_;

	CameraPtr camera_;
	GLFWwindow* window_;
	bool shouldClose_;
};

#endif /* RENDEREROGL_H_ */
