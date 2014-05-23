/*
 * Mesh.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Mesh.h"
#include "Utils.h"

#include <glm/gtc/type_ptr.hpp>
#include <iostream>
Mesh::Mesh(const std::vector<float>& geom, const std::vector<float>& colour)
	: geometry_(geom), colours_(colour), program_(-1), viewName_("") {

	GLuint geomVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, geometry_);
	GLuint colVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, colours_);

	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, geomVBO);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, colVBO);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void Mesh::setView(const glm::mat4& view) {

	glUseProgram(program_);
	glUniformMatrix4fv(viewUniform_, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void Mesh::draw() {

	  glUseProgram (program_);
	  glBindVertexArray (vao_);
	  glDrawArrays (GL_TRIANGLES, 0, geometry_.size());
	  glUseProgram (0);
}

//	Getters & Setters

const std::vector<float>& Mesh::getColours() const {
	return colours_;
}

void Mesh::setColours(const std::vector<float>& colours) {
	colours_ = colours;
}

const std::vector<float>& Mesh::getGeometry() const {
	return geometry_;
}

void Mesh::setGeometry(const std::vector<float>& geometry) {
	geometry_ = geometry;
}

GLuint Mesh::getProgram() const {
	return program_;
}

void Mesh::setProgram(GLuint program) {
	program_ = program;
	if(viewName_.size() != 0) {
		viewUniform_ = glGetUniformLocation(program_, viewName_.c_str());
	}
}

const std::string& Mesh::getViewName() const {
	return viewName_;
}

void Mesh::setViewName(const std::string& viewName) {
	viewName_ = viewName;
	if(program_ != -1) {
		viewUniform_ = glGetUniformLocation(program_, viewName_.c_str());
	}
}
