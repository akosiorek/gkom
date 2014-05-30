/*
 * IMesh.cpp
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek
 */

#include "IMesh.h"

IMesh::IMesh(const std::vector<float>& geom, const std::vector<float>& colour,
		const std::vector<unsigned>& indices, GLuint drawMode)
	: geometry_(geom), colours_(colour), indices_(indices), drawMode_(drawMode) {

		if(indices_.size() != 0) {
			drawFunc_ = std::bind(glDrawElements, drawMode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
		} else {
			drawFunc_ = std::bind(glDrawArrays, GL_TRIANGLES, 0, geometry_.size());
		}
}

//	Getters & Setters

const std::vector<float>& IMesh::getColours() const {
	return colours_;
}

void IMesh::setColours(const std::vector<float>& colours) {
	colours_ = colours;
}

const std::vector<float>& IMesh::getGeometry() const {
	return geometry_;
}

void IMesh::setGeometry(const std::vector<float>& geometry) {
	geometry_ = geometry;
}

const std::vector<float>& IMesh::getNormals() const {
	return normals_;
}

void IMesh::setNormals(const std::vector<float>& normals) {
	normals_ = normals;
}
