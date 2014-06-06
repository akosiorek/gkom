#include "Movable.h"
#include "Trajectory.h"

void Movable::addTrajectory(TrajectoryPtr trajectory) {

	trajectory->setMovable(shared_from_this());
	trajectories_.push_back(trajectory);
}

void Movable::update(double elapsedTime) {

	for(auto trajectory : trajectories_) {
		trajectory->update(elapsedTime);
	}
}
