/*
 * Mesh.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Mesh.h"

#include <glm/gtc/type_ptr.hpp>

Mesh::Mesh(GLuint program, std::string viewName)
	: program_(program), viewName_(viewName) {


}

void Mesh::setView(const glm::mat4& view) {

}


void Mesh::draw() {

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
}

const std::string& Mesh::getViewName() const {
	return viewName_;
}

void Mesh::setViewName(const std::string& viewName) {
	viewName_ = viewName;
}
