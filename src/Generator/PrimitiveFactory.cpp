#include "PrimitiveFactory.h"
#include "Box.h"
#include "NormalGenerator.h"
#include "PolyhedronGenerator.h"
#include "BasicMesh.h"

auto PrimitiveFactory::polyhedron(int vertices, float height, float upperLen, float lowerLen,
 const glm::vec3& colour, float upperDent, float lowerDent) -> NodePtr {

	auto data = PolyhedronGenerator::generate(vertices, height, upperLen,
		lowerLen, upperDent, lowerDent);
	
	auto normals = NormalGenerator::gen(data);
	auto mesh = std::make_shared<BasicMesh>(
			data,
			normals,
			colour
	);
	return std::make_shared<Node>(mesh);
}

auto PrimitiveFactory::cuboid(float height, float width, float depth,
	const glm::vec3& colour) -> NodePtr {

	auto box = std::make_shared<Box>(colour);
	box->scale(width, height, depth);
	return box;
}
