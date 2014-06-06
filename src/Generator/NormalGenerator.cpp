/*
 * NormalGenerator.cpp
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#include <NormalGenerator.h>

#include "glm/glm.hpp"

std::vector<float> NormalGenerator::gen(const std::vector<float>& vertices) {

	std::vector<float> normals;
	normals.reserve(vertices.size());
	int counter = 0;
	for(auto it = vertices.begin(); it != vertices.end();) {

		glm::vec3 a(*it++,*it++,*it++);
		glm::vec3 b(*it++,*it++,*it++);
		glm::vec3 c(*it++,*it++,*it++);
		glm::vec3 normal = glm::normalize(glm::cross(b - a, c - a));
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
		normals.push_back(normal.x);
		normals.push_back(normal.y);
		normals.push_back(normal.z);
		++counter;
	}

	return normals;
}
