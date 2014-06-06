/*
 * Box.h
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef BOX_H_
#define BOX_H_

#include "Node.h"
#include "typedefs.h"
#include "glm/glm.hpp"
#include <vector>

class Box : public Node {
public:
	Box(const glm::vec3& colour);
	Box(const std::vector<glm::vec3>& colours);
	virtual ~Box() = default;

private:
	void distribute();

};

#endif /* BOX_H_ */
