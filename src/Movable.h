/*
 * Movable.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef MOVABLE_H_
#define MOVABLE_H_

enum class Axis {X, Y, Z};

class Movable {
public:
	Movable() = default;
	virtual ~Movable() = default;

	virtual void translate(float x, float y, float z) = 0;
	virtual void roate(Axis axis, float deg) = 0;
	virtual void scale(float x, float y, float z) = 0;
};

#endif /* MOVABLE_H_ */
