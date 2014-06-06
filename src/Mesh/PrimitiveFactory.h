#ifndef PRIMITIVE_FACTORY_H
#define PRIMITIVE_FACTORY_H

#include "typedefs.h"
#include <vector>

class PrimitiveFactory {
	PrimitiveFactory() = delete;

public:
	static NodePtr polyhedron(int vertices, float height, float upperLen, float lowerLen,
	 const std::vector<float>& colour, float upperDent = .0f, float lowerDent = .0f);
	static NodePtr cuboid(float height, float width, float depth, const std::vector<float>& colour);
};

#endif // PRIMITIVE_FACTORY_H
