#include "SpaceShip.h"
#include "PrimitiveFactory.h"

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
	auto base = PrimitiveFactory::cuboid(1, 1.2, 3, colours[0]);
	corpus->addChild(base);

	auto poly = PrimitiveFactory::polyhedron(22, 1, 0.3, 0.2, colours[1]);
	poly->translate(0, 0, 4);
	poly->rotate(Axis::Z, 90);
	poly->rotate(Axis::X, 90);
	corpus->addChild(poly);

	return corpus;
}