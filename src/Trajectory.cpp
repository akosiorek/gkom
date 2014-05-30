/*
 * Trajectory.cpp
 *
 *  Created on: May 30, 2014
 *      Author: Adam Kosiorek
 */

#include <Trajectory.h>
#include "Movable.h"

void Trajectory::update(double elapsedTime) {

	if(!current_ || current_->did >= current_->max || current_->did <= -current_->max) {
		if(moveQueue_.empty()) {
			return;
		} else {
			current_ = std::move(moveQueue_.front());
			moveQueue_.pop_front();
		}
	}

	float extent = current_->speed * elapsedTime;
	current_->did += extent;
	move(current_->type, extent);
}

void Trajectory::addMove(float speed, float max, MoveType type) {
	moveQueue_.emplace_back(new Params(speed, max, type));
}

void Trajectory::move(MoveType type, float extent) {

	switch(type) {
	case MoveType::TransX: movable_->translate(extent, 0, 0); break;
	case MoveType::TransY: movable_->translate(0, extent, 0); break;
	case MoveType::TransZ: movable_->translate(0, 0, extent); break;
	case MoveType::RotX: movable_->rotate(Axis::X, extent); break;
	case MoveType::RotY: movable_->rotate(Axis::Y, extent); break;
	case MoveType::RotZ: movable_->rotate(Axis::Z, extent); break;
	}
}

void Trajectory::setMovable(MovablePtr movable) {
	movable_ = movable;
}
