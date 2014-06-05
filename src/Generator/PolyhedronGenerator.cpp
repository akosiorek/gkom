#include "PolyhedronGenerator.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

std::vector<float> PolyhedronGenerator::generate(int numVertices, float height, float upperLength, float lowerLength) {

	std::vector<float> vertices;
	//	There are 2 * size triangles so 6 * size vertices
	vertices.reserve(6 * numVertices);

	VertVec upperBase = genarateBase(numVertices, upperLength);
	translateVec(upperBase, height/2);
	VertVec lowerBase = genarateBase(numVertices, lowerLength);
	translateVec(lowerBase, -height/2);	

	triangulate(vertices, upperBase, lowerBase);
	triangulate(vertices, lowerBase, upperBase, 1);	
	genLid(vertices, upperBase);
	genLid(vertices, lowerBase, true);

	return vertices;
}

std::vector<glm::vec3> PolyhedronGenerator::genarateBase(int vertices, float edgeLength) {

	VertVec baseVertices;
	baseVertices.reserve(vertices);
	float radius = circumRadius(vertices, edgeLength);
	float angle = interiorAngle(vertices);
	const glm::vec3 axis(0, 0, 1);

	glm::vec3 vertex(0, 0, radius);

	for(int i = 0; i < vertices; ++i) {

		baseVertices.push_back(vertex);
		// vertex = glm::rotate(vertex, angle, axis);
		rotateVertex(vertex, angle);
	}
	return baseVertices;
}

float PolyhedronGenerator::circumRadius(int vertices, float edgeLength) {
	return .5f * edgeLength / std::sin(M_PI / vertices);
}

float PolyhedronGenerator::interiorAngle(int vertices) {
	return 360.0f / vertices;
}

void PolyhedronGenerator::translateVec(VertVec& vec, float distance) {

	for(auto& vertex : vec) {
		vertex.y += distance;
	}
}

void PolyhedronGenerator::rotateVertex(glm::vec3& vertex, float angle) {

	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0));
	vertex = glm::mat3(rotation) * vertex;
}

void PolyhedronGenerator::triangulate(std::vector<float> &destVec, const VertVec& vec1, const VertVec& vec2, int offset) {

	size_t last = vec1.size() - 1;
	for(int i = 0; i < last; ++i ) {

		if(offset) {

			pushVertex(destVec, vec2[i + offset]);			
			pushVertex(destVec, vec1[i + 1]);
			pushVertex(destVec, vec1[i]);
		
		} else {
			pushVertex(destVec, vec1[i]);
			pushVertex(destVec, vec1[i + 1]);
			pushVertex(destVec, vec2[i + offset]);
		}
	}

	if(offset) {

		pushVertex(destVec, vec2[offset ? 0 : last]);			
		pushVertex(destVec, vec1[0]);	
		pushVertex(destVec, vec1[last]);
	
	} else {
		pushVertex(destVec, vec1[last]);
		pushVertex(destVec, vec1[0]);	
		pushVertex(destVec, vec2[offset ? 0 : last]);
	}


	
}

void PolyhedronGenerator::pushVertex(std::vector<float>& vec, const glm::vec3 vert) {

	vec.push_back(vert.x);
	vec.push_back(vert.y);
	vec.push_back(vert.z);
}

void PolyhedronGenerator::genLid(std::vector<float>& destVec, const VertVec& vertices, bool reverse) {

	float y = vertices[0].y;
	size_t last = vertices.size() - 1;
	if(!reverse) {
	for(int i = 0; i < last; ++i) {

		pushVertex(destVec, vertices[i + 1]);		
		pushVertex(destVec, vertices[i]);
		pushVertex(destVec, glm::vec3(0, y, 0));
		
	}
	pushVertex(destVec, vertices[0]);		
	pushVertex(destVec, vertices[last]);
	pushVertex(destVec, glm::vec3(0, y, 0));
	
	}	else {

			for(int i = 0; i < last; ++i) {

		pushVertex(destVec, glm::vec3(0, y, 0));
		pushVertex(destVec, vertices[i]);
		pushVertex(destVec, vertices[i + 1]);
	}
	pushVertex(destVec, glm::vec3(0, y, 0));
	pushVertex(destVec, vertices[last]);
	pushVertex(destVec, vertices[0]);
	}	

}






