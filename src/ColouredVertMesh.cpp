/*
 * ColouredVertMesh.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "ColouredVertMesh.h"
#include "Utils.h"
#include "MeshConfig.h"

#include <glm/gtc/type_ptr.hpp>

ColouredVertMesh::ColouredVertMesh(const std::vector<float>& geom, const std::vector<float>& colour,
		const std::vector<unsigned>& indices, GLuint drawMode)
	: IMesh(geom, colour, indices, drawMode) {

	GLuint geomVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, geometry_);
	GLuint colVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, colours_);

	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, geomVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, colVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	viewUniform_ = glGetUniformLocation(MeshConfig::COLORED_VERT_PROGRAM, MeshConfig::PERSPECTIVE_UNIFORM_NAME.c_str());
}

void ColouredVertMesh::setView(const glm::mat4& view) {

	glUseProgram(MeshConfig::COLORED_VERT_PROGRAM);
	glUniformMatrix4fv(viewUniform_, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void ColouredVertMesh::draw() {

	  glUseProgram (MeshConfig::COLORED_VERT_PROGRAM);
	  glBindVertexArray (vao_);
	  drawFunc_();
	  glUseProgram (0);
}


