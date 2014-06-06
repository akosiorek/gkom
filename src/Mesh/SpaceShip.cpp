#include "SpaceShip.h"
#include "PrimitiveFactory.h"
#include "Trajectory.h"

SpaceShip::SpaceShip() {

	std::vector<float> red = {1, 0.5, 0};
	std::vector<float> blue = {0, 0.5, 1};
	build(std::vector<std::vector<float>>({blue, red}));

}

SpaceShip::SpaceShip(const std::vector<std::vector<float>>& colours) {

	build(colours);
}

void SpaceShip::build(const std::vector<std::vector<float>>& colours) {

	addChild(buildCorpus(colours));

	// auto right = buildSide(colours);
	// right->translate(1, 0, 0);
	// addChild(right);

	// auto left = buildSide(colours);
	// left->rotate(Axis::Z, 180);
	// left->translate(0, 0, 1);
	// addChild(left);
}

auto SpaceShip::buildSide(const std::vector<std::vector<float>>& colours) -> NodePtr {


}

auto SpaceShip::buildCorpus(const std::vector<std::vector<float>>& colours) -> NodePtr {

	auto corpus = std::make_shared<Node>();
	auto base = PrimitiveFactory::cuboid(0.8, 1.1, 3, colours[0]);
	corpus->addChild(base);

	auto headFront = PrimitiveFactory::polyhedron(22, 0.3, 0.24, 0.2, colours[1], 1);
	headFront->translate(0, 0, 3.55);
	headFront->rotate(Axis::Z, 90);
	headFront->rotate(Axis::X, 90);
	auto headRotation = std::make_shared<Trajectory>();
	headRotation->addMove(360 * 2.5, 0, MoveType::RotY);
	headFront->addTrajectory(headRotation);
	corpus->addChild(headFront);


	std::shared_ptr<Node> sticks[4];
	float stickPositions[][3] = {{0.28, 0, 0}, {-0.28, 0, 0}, {0, 0, 0.28}, {0, 0, -0.28}};
	for(int i = 0; i < 4; ++i) {
		sticks[i] = PrimitiveFactory::polyhedron(22, 0.6, 0.023, 0.023, colours[0]);
		sticks[i]->translate(0, .3, 0);
		sticks[i]->translate(stickPositions[i][0], stickPositions[i][1], stickPositions[i][2]);	
		headFront->addChild(sticks[i]);
	} 

	auto headBack = PrimitiveFactory::polyhedron(22, 0.4, 0.2, 0.2, colours[1]);
	headBack->translate(0, 0, 3.2);
	headBack->rotate(Axis::Z, 90);
	headBack->rotate(Axis::X, 90);
	corpus->addChild(headBack);


	float bridgeZ = -1.3;
	int bridgeVertices = 6;
	float bridgePolyHeight = 0.5;
	float bridgeShortEdge = 0.5;
	float bridgeLongEdge = 1.0f;

	auto bridgeBase = PrimitiveFactory::polyhedron(22, 0.4, 0.15, 0.15, colours[1]);
	bridgeBase->translate(0, 1, bridgeZ);
	corpus->addChild(bridgeBase);

	auto bridgeMid = PrimitiveFactory::polyhedron(bridgeVertices, bridgePolyHeight, bridgeShortEdge, bridgeLongEdge, colours[1]);
	bridgeMid->translate(0, 1.45, bridgeZ);
	auto brideMidRot = std::make_shared<Trajectory>();
	brideMidRot->addMove(-180, 0, MoveType::RotY);
	bridgeMid->addTrajectory(brideMidRot);
	corpus->addChild(bridgeMid);

	auto bridgeTop = PrimitiveFactory::polyhedron(bridgeVertices, bridgePolyHeight, bridgeLongEdge, bridgeShortEdge, colours[1]);
	bridgeTop->translate(0, 1.95, bridgeZ);
	auto bridgeTopRot = std::make_shared<Trajectory>();
	bridgeTopRot->addMove(180, 0, MoveType::RotY);
	bridgeTop->addTrajectory(bridgeTopRot);
	corpus->addChild(bridgeTop);


	corpus->addChild(bridgeBase);

	return corpus;
}