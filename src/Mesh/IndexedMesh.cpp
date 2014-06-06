/*
 * IndexedMesh.cpp
 *
 *  Created on: Jun 6, 2014
 *      Author: Adam Kosiorek
 */

#include "IndexedMesh.h"
#include "Utils.h"
#include "MeshConfig.h"

#include <glm/gtc/type_ptr.hpp>

IndexedMesh::IndexedMesh(const std::vector<float>& geometry, const std::vector<float>& normals,
		const std::vector<uint>& indices, const glm::vec3& colour, GLuint drawMode)
	: IMesh(geometry, drawMode), normals_(normals), indices_(indices), colour_(colour) {


	GLuint geomVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, geometry_);
	GLuint normalVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals_);

	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, geomVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	viewUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::PERSPECTIVE_UNIFORM_NAME.c_str());
	colourUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::COLOUR_UNIFORM_NAME.c_str());
	normalUniform_ = glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::NORMAL_UNIFORM_NAME.c_str());
}

void IndexedMesh::setView(const glm::mat4& view) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniformMatrix4fv(viewUniform_, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void IndexedMesh::setNormalTransform(const glm::mat3 normalTransform) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniformMatrix4fv(normalUniform_, 1, GL_FALSE, glm::value_ptr(normalTransform));
	glUseProgram(0);
}

void IndexedMesh::setColour(const glm::vec3& colour) {
	colour_ = colour;
}

void IndexedMesh::draw() {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniform3fv(colourUniform_, 1, glm::value_ptr(colour_));
	glBindVertexArray (vao_);
	glDrawElements(drawMode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
	glUseProgram (0);
}
