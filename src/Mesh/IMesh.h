/*
 * IMesh.h
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef IMESH_H_
#define IMESH_H_

#include <GL/glew.h>
#include "glm/glm.hpp"
#include <vector>

class IMesh {
public:
	IMesh(const std::vector<float>& geometry, GLuint drawMode)
	: geometry_(geometry), drawMode_(drawMode) {};

	virtual ~IMesh() = default;

	virtual void setView(const glm::mat4& view) = 0;
	virtual void draw() = 0;

protected:
	std::vector<float> geometry_;
	GLuint drawMode_;
};

#endif /* IMESH_H_ */
