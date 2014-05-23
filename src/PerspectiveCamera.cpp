/*
 * PerspectiveCamera.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

const float PerspectiveCamera::degToRad_ = 3.14159f * 2.0f / 360.0f;

PerspectiveCamera::PerspectiveCamera()
	: ratio_(1.0f), scale_(1.0f), transform_(.0f) {

	transform_[0][0] = scale_;
	transform_[1][1] = scale_;

	setDistance(1.0f);
	setClipping(0.5f, 3.0f);
}


void PerspectiveCamera::translate(float x, float y, float z) {
	transform_ = glm::translate(transform_, glm::vec3(x, y, z));
}

void PerspectiveCamera::rotate(Axis axis, float deg) {
	switch(axis) {
		case Axis::X: transform_ = glm::rotate(transform_, deg, glm::vec3(1.0f, .0f, .0f)); break;
		case Axis::Y: transform_ = glm::rotate(transform_, deg, glm::vec3(.0f, 1.0f, .0f)); break;
		case Axis::Z: transform_ = glm::rotate(transform_, deg, glm::vec3(.0f, .0f, 1.0f)); break;
	}

}

void PerspectiveCamera::pointAt(float x, float y, float z) {

}

void PerspectiveCamera::setFOV(float fov) {

	float scale = 1.0f / tan(fov * degToRad_ / 2.0f);
	if(scale != scale_) {
		scale_ = scale;
		transform_[0][0] = scale_ * ratio_;
		transform_[1][1] = scale_;
	}
}

void PerspectiveCamera::setRatio(int width, int height) {

	float ratio = float(width) / height;
	if(ratio != ratio_) {
		ratio_ = ratio;
		transform_[0][0] = scale_ * ratio;
	}
}

void PerspectiveCamera::setDistance(float distance) {
	transform_[2][3] = -distance;
}

void PerspectiveCamera::setClipping(float near, float far) {

	if(near != near_ || far != far_) {
		near_ = near;
		far_ = far;
		transform_[2][2] = (far_ + near_) / (near_ - far_);
		transform_[3][2] = (2 * far_ * near_) / (near_ - far_);
	}
}

const glm::mat4& PerspectiveCamera::getTransform() const {
	return transform_;
}

void PerspectiveCamera::setTransform(const glm::mat4& transform) {
	transform_ = transform;
}
