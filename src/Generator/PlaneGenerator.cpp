/*
 * PlaneGenerator.cpp
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#include "PlaneGenerator.h"
#include "Utils.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

std::vector<float> PlaneGenerator::genVertices(int width, int height, int noise) const {

	std::vector<float> vertices;
	vertices.reserve(width * height * 3);


	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			vertices.push_back(col);
			vertices.push_back(noise ? float(rand() % noise) / 100 : 0);
			vertices.push_back(row);
		}
	}
	return vertices;
}

std::vector<unsigned> PlaneGenerator::genIndices(int width, int height) const {

	std::vector<unsigned> indices;
	indices.reserve((2 * width + 2) * (height - 1));

    for (int r = 0; r < height - 1; ++r) {
        indices.push_back(r * width);
        for (int c = 0; c < width; ++c) {
            indices.push_back(r * width + c);
            indices.push_back((r + 1) * width + c);
        }
        indices.push_back((r + 1) * width + (width - 1));
    }
    return indices;
}

glm::vec3 PlaneGenerator::getVert(unsigned v) const {

	v *= 3;
	return glm::vec3(vertices_[v], vertices_[v+1], vertices_[v+2]);
}

std::vector<float> PlaneGenerator::genNormals(int width, int height) const {

	std::vector<glm::vec3> averaged(vertices_.size() / 3);
	glm::vec3 vert[3];
	unsigned ind[3];

	auto it = ++indices_.begin();
	for(int i = 0; i < 3; ++i) {
		ind[i] = *it++;
		vert[i] = getVert(ind[i]);
	}

	for(; it != indices_.end();) {
		glm::vec3 normal = glm::cross(vert[0] - vert[1], vert[0] - vert[2]);
		normal = glm::normalize(normal);

		for(int i = 0; i < 3; ++i) {
			averaged[ind[i]] += normal;
		}

		vert[0] = vert[1];
		vert[1] = vert[2];

		ind[0] = ind[1];
		ind[1] = ind[2];
		if(ind[2] % 100 == 99 && ind[2] > 100 && *it < (width * height - 1)) {
			++(++(++it));
		}
		ind[2] = *it++;
		vert[2] = getVert(ind[2]);

	}

	std::vector<float> normals;
	normals.reserve(vertices_.size());
	for(auto& avg : averaged) {
		avg = glm::normalize(avg);

		normals.push_back(avg.x);
		normals.push_back(avg.y);
		normals.push_back(avg.z);
	}

	return normals;
}

void PlaneGenerator::generate(int width, int height, int noise) {
	vertices_ = genVertices(width, height, noise);
	indices_ = genIndices(width, height);
	normals_ = genNormals(width, height);
	Utils::dumpVec(normals_, "normal.txt");
}

void PlaneGenerator::displace(int x, int y, float dx, float dy, float dz) {
	//TODO
}

const std::vector<unsigned>& PlaneGenerator::getIndices() const {
	return indices_;
}

void PlaneGenerator::setIndices(const std::vector<unsigned>& indices) {
	indices_ = indices;
}

const std::vector<float>& PlaneGenerator::getVertices() const {
	return vertices_;
}

void PlaneGenerator::setVertices(const std::vector<float>& vertices) {
	vertices_ = vertices;
}

const std::vector<float>& PlaneGenerator::getNormals() const {
	return normals_;
}

void PlaneGenerator::setNormals(const std::vector<float>& normals) {
	normals_ = normals;
}
