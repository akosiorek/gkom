#ifndef SPACE_SHIP_H
#define SPACE_SHIP_H

#include "Node.h"

#include <vector>

class SpaceShip : public Node {
private:
	/* data */
public:
	SpaceShip();
	SpaceShip(const std::vector<std::vector<float>>& colours);

private:
	void build(const std::vector<std::vector<float>>& colours);
	NodePtr buildSide(const std::vector<std::vector<float>>& colours);
	NodePtr buildCorpus(const std::vector<std::vector<float>>& colours);
};

#endif // SPACE_SHIP_H
