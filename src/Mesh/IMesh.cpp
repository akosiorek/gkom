/*
 * IMesh.cpp
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#include "IMesh.h"

IMesh::IMesh(const std::vector<float>& geom, const std::vector<float>& normals, const std::vector<float>& colour,
		const std::vector<unsigned>& indices, GLuint drawMode)
	: geometry_(geom), normals_(normals), colours_(colour), indices_(indices), drawMode_(drawMode) {

		if(indices_.size() != 0) {
			drawFunc_ = std::bind(glDrawElements, drawMode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
		} else {
			drawFunc_ = std::bind(glDrawArrays, GL_TRIANGLES, 0, geometry_.size());
		}
}
