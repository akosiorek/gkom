/*
 * IMesh.h
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef IMESH_H_
#define IMESH_H_

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <vector>
#include <functional>

class IMesh {
public:
	IMesh(const std::vector<float>& geom, const std::vector<float>& normals, const std::vector<float>& colour,
			const std::vector<unsigned>& indices, GLuint drawMode);

	virtual ~IMesh() = default;

	virtual void setView(const glm::mat4& view) = 0;
	virtual void draw() = 0;

protected:
	std::vector<float> geometry_;
	std::vector<float> colours_;
	std::vector<float> normals_;
	std::vector<unsigned> indices_;
	GLuint drawMode_;
	std::function<void(void)> drawFunc_;
};

#endif /* IMESH_H_ */