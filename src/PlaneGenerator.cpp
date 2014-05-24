/*
 * PlaneGenerator.cpp
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek
 */

#include "PlaneGenerator.h"

#include <ctime>
#include <cstdlib>

std::vector<float> PlaneGenerator::genVertices(int width, int height, int noise) {

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

std::vector<unsigned> PlaneGenerator::genIndices(int width, int height) {

	std::vector<unsigned> indices;
	indices.reserve((width * height) + (width - 1) * (height - 2));

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

void PlaneGenerator::generate(int width, int height, int noise) {
	vertices_ = genVertices(width, height, noise);
	indices_ = genIndices(width, height);
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
