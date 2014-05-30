/*
 * Box.h
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek
 */

#ifndef BOX_H_
#define BOX_H_

#include <Node.h>
#include "typedefs.h"
#include <vector>

class Box: public Node {
public:
	Box(std::vector<float>& colour);
	Box(std::vector<std::vector<float>>& colours);
	virtual ~Box() = default;

private:
	void distribute();

};

#endif /* BOX_H_ */
