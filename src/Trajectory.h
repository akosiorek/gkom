/*
 * Trajectory.h
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef TRAJECTORY_H_
#define TRAJECTORY_H_

#include "typedefs.h"
#include <list>

enum class MoveType {
	TransX,
	TransY,
	TransZ,
	RotX,
	RotY,
	RotZ
};

class Trajectory {
public:
	Trajectory() = default;
	virtual ~Trajectory() = default;

	void update(double elapsedTime);
	void addMove(float speed, float max, MoveType type);
	void setMovable(MovablePtr movable);

private:
	void move(MoveType type, float extent);


	struct Params {
		Params(float speed, float max, MoveType type)
		: max(max), speed(speed), type(type), did(0) {};

		float max;
		float speed;
		MoveType type;
		float did;
	};

	typedef std::unique_ptr<Params> ParamsPtr;

	MovablePtr movable_;
	ParamsPtr current_;
	std::list<ParamsPtr> moveQueue_;
};

#endif /* TRAJECTORY_H_ */
