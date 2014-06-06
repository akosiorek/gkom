#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "Node.h"

#include <vector>

class SpaceShip : public Node {
public:
	SpaceShip();
	SpaceShip(const std::vector<std::vector<float>>& colours);

private:
	void build(const std::vector<std::vector<float>>& colours);
	NodePtr buildSide(const std::vector<std::vector<float>>& colours);
	NodePtr buildCorpus(const std::vector<std::vector<float>>& colours);
	NodePtr buildBridge(const std::vector<std::vector<float>>& colours);

private:
	const static float baseHeight_;
	const static int bridgeVertices_;
	const static float bridgePolyHeight_;
	const static float bridgeShortEdge_;
	const static float bridgeLongEdge_;
	const static float bridgeBaseHeight_;

};

#endif // SPACE_SHIP_H
