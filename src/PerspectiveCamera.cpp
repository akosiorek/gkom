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
	: ratio_(764.f / 1024.f),
	fov_(90.f),
	near_(0.5f),
	far_(3.0f),
	position_(.0f, .0f, .0f),
	target_(.0f, .0f, -1.0f),
	up_(.0f, 1.f, .0f),
	rotation_(1.0f),
	projection_(.0f),
	view_(.0f),
	model_(1.0f),
	transform_(.0f),
	outdated_(true) {

	updateView();
	updateProjection();
}

void PerspectiveCamera::updateView() {

	view_ = glm::lookAt(position_, target_, up_);
	outdated_ = true;
}

void PerspectiveCamera::updateProjection() {

	projection_ = glm::perspective(fov_, ratio_, near_, far_);
	outdated_ = true;
}

void PerspectiveCamera::updateTransform() const {

	if(outdated_) {
		transform_ = projection_ * view_ * model_;
		outdated_ = false;
	}
}

void PerspectiveCamera::translate(float x, float y, float z) {
	position_ += glm::vec3(x, y, -z);
	updateView();

}

void PerspectiveCamera::rotate(Axis axis, float deg) {

	glm::vec3 tmp;
	switch(axis) {
	case Axis::X: tmp = glm::vec3(1.0f, .0f, .0f); break;
	case Axis::Y: tmp = glm::vec3(.0f, 1.0f, .0f); break;
	case Axis::Z: tmp = glm::vec3(.0f, .0f, 1.0f); break;
	}

	model_ = glm::rotate(model_, deg, tmp);
	outdated_ = true;
}

void PerspectiveCamera::pointAt(float x, float y, float z) {
	target_ = glm::vec3(x, y, z);
	updateView();
}

void PerspectiveCamera::setFOV(float fov) {

	fov_ = fov;
	updateProjection();
}

void PerspectiveCamera::setRatio(int width, int height) {

	ratio_ = float(height) / width;
	updateProjection();
}

void PerspectiveCamera::setDistance(float distance) {
	transform_[2][3] = -distance;
}

void PerspectiveCamera::setClipping(float near, float far) {

	near_ = near;
	far_ = far;
	updateProjection();
}

const glm::mat4& PerspectiveCamera::getTransform() const {
	updateTransform();
	return transform_;
}

void PerspectiveCamera::setTransform(const glm::mat4& transform) {
	transform_ = transform;
	outdated_ = false;
}
