/*
 * UniformColouredMesh.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "UniformColouredMesh.h"
#include "Utils.h"
#include "MeshConfig.h"

#include <glm/gtc/type_ptr.hpp>

UniformColouredMesh::UniformColouredMesh(const std::vector<float>& geom, const std::vector<float>& colour,
		const std::vector<unsigned>& indices, GLuint drawMode)
	: IMesh(geom, colour, indices, drawMode) {

	GLuint geomVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, geometry_);

	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, geomVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	viewUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::PERSPECTIVE_UNIFORM_NAME.c_str());
	colourUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::COLOUR_UNIFORM_NAME.c_str());
	normalUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::NORMAL_UNIFORM_NAME.c_str());

}

void UniformColouredMesh::setView(const glm::mat4& view) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniformMatrix4fv(viewUniform_, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void UniformColouredMesh::setNormalTransform(const glm::mat3 normalTransform) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniformMatrix4fv(normalUniform_, 1, GL_FALSE, glm::value_ptr(normalTransform));
	glUseProgram(0);
}

void UniformColouredMesh::draw() {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniform3f(colourUniform_, colours_[0], colours_[1],colours_[2]);
	glBindVertexArray (vao_);
	drawFunc_();
	glUseProgram (0);
}

void UniformColouredMesh::setNormals(const std::vector<float>& normals) {

	IMesh::setNormals(normals);

	GLuint normalVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals_);

	glBindVertexArray (vao_);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}


