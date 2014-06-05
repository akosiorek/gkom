#include "PrimitiveFactory.h"
#include "Box.h"
#include "NormalGenerator.h"
#include "PolyhedronGenerator.h"
#include "UniformColouredMesh.h"

auto PrimitiveFactory::polyhedron(int vertices, float height, 
	float upperLen, float lowerLen, const std::vector<float>& colour) -> NodePtr {

	auto data = PolyhedronGenerator::generate(vertices, height, upperLen, lowerLen);
	auto normals = NormalGenerator::gen(data);
	auto mesh = std::make_shared<UniformColourMesh>(
			data,
			normals,
			colour
	);
	return std::make_shared<Node>(mesh);
}


auto PrimitiveFactory::cuboid(float height, float width, float depth,
	const std::vector<float>& colour) -> NodePtr {

	auto box = std::make_shared<Box>(colour);
	box->scale(width, height, depth);
	return box;
}	