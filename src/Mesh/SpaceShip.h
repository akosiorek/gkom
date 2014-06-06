#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "Node.h"

#include "glm/glm.hpp"
#include <vector>

class SpaceShip : public Node {
public:
	SpaceShip();
	SpaceShip(const std::vector<glm::vec3>& colours);

private:
	void build(const std::vector<glm::vec3>& colours);
	NodePtr buildSide(const std::vector<glm::vec3>& colours);
	NodePtr buildCorpus(const std::vector<glm::vec3>& colours);
	NodePtr buildBridge(const std::vector<glm::vec3>& colours);

private:
	const static float baseHeight_;
	const static int bridgeVertices_;
	const static float bridgePolyHeight_;
	const static float bridgeShortEdge_;
	const static float bridgeLongEdge_;
	const static float bridgeBaseHeight_;

};

#endif // SPACE_SHIP_H
