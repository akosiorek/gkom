/*
 * PerspectiveCamera.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "PerspectiveCamera.h"

const float PerspectiveCamera::degToRad_ = 3.14159f * 2.0f / 360.0f;

PerspectiveCamera::PerspectiveCamera()
	: ratio_(1.0f), scale_(1.0f) {

	transform_[0][0] = scale_;
	transform_[1][1] = scale_;
	transform_[2][3] = -1.0f;

	setClipping(0.5f, 3.0f);
}


void PerspectiveCamera::translate(float x, float y, float z) {

}

void PerspectiveCamera::roate(Axis axis, float deg) {

}

void PerspectiveCamera::scale(float x, float y, float z) {

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
