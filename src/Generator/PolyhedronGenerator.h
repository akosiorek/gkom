#ifndef POLYHEDRON_GENERATOR_H
#define POLYHEDRON_GENERATOR_H

#include "glm/glm.hpp"
#include <vector>

class PolyhedronGenerator {
	typedef std::vector<glm::vec3> VertVec;
public:
	PolyhedronGenerator(/* args */) = default;

	static std::vector<float> generate(int vert, float height, float upperLength, float lowerLength);

private:
	static std::vector<glm::vec3> genarateBase(int vert, float edgeLength);
	static float circumRadius(int vertices, float edgeLength);
	static float interiorAngle(int vertices);
	static void translateVec(VertVec& vec, float distance);
	static void rotateVertex(glm::vec3& vertex, float angle);
	static void triangulate(std::vector<float> &destVec, const VertVec& vec1, const VertVec& vec2, int offset = 0);
	static void pushVertex(std::vector<float>& vec, const glm::vec3 vert);
	static void genLid(std::vector<float>& destVec, const VertVec& vertices, bool reverse = false);
};

#endif // POLYHEDRON_GENERATOR_H

