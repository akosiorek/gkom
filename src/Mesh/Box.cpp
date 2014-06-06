/*
 * Box.cpp
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#include <Box.h>
#include "BasicMesh.h"
#include "Utils.h"
#include "NormalGenerator.h"

Box::Box(const glm::vec3& colour) {

	//simple plane
	std::vector<float> planeGeom = Utils::loadVertexData("plane.vert");
	auto planeNormals = NormalGenerator::gen(planeGeom);

	auto mesh = std::make_shared<BasicMesh>(planeGeom, planeNormals, colour);

	for(int i = 0; i < 6; ++i) {
		addChild(std::make_shared<Node>(mesh));
	}

	distribute();
}

Box::Box(const std::vector<glm::vec3>& colours) {

	//simple plane
	std::vector<float> planeGeom = Utils::loadVertexData("plane.vert");
	auto planeNormals = NormalGenerator::gen(planeGeom);

	for(const auto& colour : colours) {
		addChild(std::make_shared<Node>(std::make_shared<BasicMesh>(planeGeom, planeNormals, colour)));
	}

	distribute();
}

void Box::distribute() {

//	Right
	auto boxNode = nodes_.begin();
	(*boxNode)->translate(1);
	(*boxNode)->rotate(Axis::Z, -90);

//Left
	++boxNode;
	(*boxNode)->translate(-1);
	(*boxNode)->rotate(Axis::Z, 90);

//	Top
	++boxNode;
	(*boxNode)->translate(0, 1);

//	Bottom
	++boxNode;
	(*boxNode)->translate(0, -1);
	(*boxNode)->rotate(Axis::Z, -180);

//	Front
	++boxNode;
	(*boxNode)->translate(0, 0, 1);
	(*boxNode)->rotate(Axis::X, 90);

//	Back
	++boxNode;
	(*boxNode)->translate(0, 0, -1);
	(*boxNode)->rotate(Axis::X, -90);


}
