#include "SpaceShip.h"
#include "PrimitiveFactory.h"
#include "Trajectory.h"

const float SpaceShip::baseHeight_ = 0.8;
const int SpaceShip::bridgeVertices_ = 6;
const float SpaceShip::bridgePolyHeight_ = 0.5;
const float SpaceShip::bridgeShortEdge_ = 0.5;
const float SpaceShip::bridgeLongEdge_ = 1.0f;
const float SpaceShip::bridgeBaseHeight_ = 1.f;


SpaceShip::SpaceShip() {

	glm::vec3 red(1, 0, 0);
	glm::vec3 blue(0, 1, 0);
	build({blue, red});
}

SpaceShip::SpaceShip(const std::vector<glm::vec3>& colours) {
	build(colours);
}

void SpaceShip::build(const std::vector<glm::vec3>& colours) {

	addChild(buildCorpus(colours));

	auto right = buildSide(colours);
	right->translate(1.1, 0, 0);
	addChild(right);

	auto left = buildSide(colours);
	left->rotate(Axis::Z, 180);
	left->translate(1.1);
	addChild(left);
}

auto SpaceShip::buildSide(const std::vector<glm::vec3>& colours) -> NodePtr {

	auto side = std::make_shared<Node>();

	auto bumper = PrimitiveFactory::polyhedron(4, 1.4f, 1.4f, 1.4f, colours[1]);
	bumper->translate(-0.1, 0, 2.f);
	bumper->scale(.5, 1.5, 1);
	bumper->rotate(Axis::Y, 45);
	side->addChild(bumper);

	auto frontWing = PrimitiveFactory::polyhedron(4, 1.9, .8f, 1.4f, colours[0]);
	frontWing->translate(1.f, 0, 2.f);
	frontWing->scale(1, 0.6, 1);
	frontWing->rotate(Axis::Z, -90);
	frontWing->rotate(Axis::Y, 45);
	side->addChild(frontWing);

	auto rearWing = PrimitiveFactory::polyhedron(4, 3.f, 1.f, 2.f, colours[1]);
	rearWing->translate(1.5f, 0, -.8f);
	rearWing->scale(1, 0.6, 1);
	rearWing->rotate(Axis::Z, -90);
	rearWing->rotate(Axis::Y, 45);	
	side->addChild(rearWing);


	NodePtr missiles[2];
	float missileY[] = {.4, -.4};
	for(int i = 0; i < 2; ++i) {

		missiles[i] = PrimitiveFactory::polyhedron(22, 2.4f, .035f, .03f, colours[0]);
		missiles[i]->translate(2.6f, missileY[i], -.8f);
		missiles[i]->rotate(Axis::Z, 90);
		missiles[i]->rotate(Axis::X, 90);
		side->addChild(missiles[i]);
	}

	return side;
}

auto SpaceShip::buildBridge(const std::vector<glm::vec3>& colours) -> NodePtr {

	float relativeZ = .5f * bridgeBaseHeight_;
	auto bridge = std::make_shared<Node>();
	bridge->translate(0, relativeZ);


	auto bridgeBase = PrimitiveFactory::polyhedron(4, bridgeBaseHeight_, 0.8, 0.8, colours[1]);
	bridgeBase->scale(1, 1, 1.25);
	bridgeBase->rotate(Axis::Y, 45);
	bridge->addChild(bridgeBase);

	auto frontWedge = PrimitiveFactory::polyhedron(4, bridgeBaseHeight_, 0.3, 0.8, colours[1]);
	frontWedge->translate(0, -bridgeBaseHeight_ * .4f, 0.9f);
	frontWedge->rotate(Axis::Z, 90);
	frontWedge->rotate(Axis::X, 90);
	frontWedge->rotate(Axis::Y, 45);
	bridge->addChild(frontWedge);


	relativeZ += bridgePolyHeight_ * 0.5;
	auto bridgeMid = PrimitiveFactory::polyhedron(bridgeVertices_, bridgePolyHeight_, bridgeShortEdge_, bridgeLongEdge_, colours[1]);
	bridgeMid->translate(0, relativeZ);
	auto brideMidRot = std::make_shared<Trajectory>();
	brideMidRot->addMove(-180, 0, MoveType::RotY);
	bridgeMid->addTrajectory(brideMidRot);
	bridge->addChild(bridgeMid);

	relativeZ += bridgePolyHeight_;
	auto bridgeTop = PrimitiveFactory::polyhedron(bridgeVertices_, bridgePolyHeight_, bridgeLongEdge_, bridgeShortEdge_, colours[1]);
	bridgeTop->translate(0, relativeZ);
	auto bridgeTopRot = std::make_shared<Trajectory>();
	bridgeTopRot->addMove(180, 0, MoveType::RotY);
	bridgeTop->addTrajectory(bridgeTopRot);
	bridge->addChild(bridgeTop);

	return bridge;
}

auto SpaceShip::buildCorpus(const std::vector<glm::vec3>& colours) -> NodePtr {

	auto corpus = std::make_shared<Node>();
	auto base = PrimitiveFactory::cuboid(baseHeight_, 1.1, 2, colours[0]);
	corpus->addChild(base);

	auto headFront = PrimitiveFactory::polyhedron(22, 0.3, 0.19, 0.18, colours[1], 1);
	headFront->translate(0, 0, 2.55);
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

	auto headBack = PrimitiveFactory::polyhedron(22, 0.4, 0.18, 0.18, colours[1]);
	headBack->translate(0, 0, 2.2);
	headBack->rotate(Axis::Z, 90);
	headBack->rotate(Axis::X, 90);
	corpus->addChild(headBack);

	auto bridge = buildBridge(colours);
	bridge->translate(0, baseHeight_, -1.3f);
	corpus->addChild(bridge);
	
	return corpus;
}
