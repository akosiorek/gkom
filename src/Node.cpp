/*
 * Node.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Node.h"
#include "IMesh.h"

#include <glm/gtc/matrix_transform.hpp>

Node::Node(MeshPtr mesh)
	: mesh_(mesh) {}


void Node::draw(const glm::mat4& transform) {

	auto currentTransform = transform * transform_;
//	auto currentNormalTransform = glm::transpose(glm::inverse(glm::mat3(currentTransform)));
	if(mesh_) {
		mesh_->setView(currentTransform);//, currentNormalMatrix);
		mesh_->draw();
	}

	for(auto child : nodes_) {
		child->draw(currentTransform);
	}
}

void Node::translate(float x, float y, float z) {
	transform_ = glm::translate(transform_, glm::vec3(x, y, z));
}

void Node::rotate(Axis axis, float deg) {
	switch(axis) {
		case Axis::X: transform_ = glm::rotate(transform_, deg, glm::vec3(1.0f, .0f, .0f)); break;
		case Axis::Y: transform_ = glm::rotate(transform_, deg, glm::vec3(.0f, 1.0f, .0f)); break;
		case Axis::Z: transform_ = glm::rotate(transform_, deg, glm::vec3(.0f, .0f, 1.0f)); break;
	}
}

void Node::scale(float x, float y, float z) {
	transform_ = glm::scale(transform_, glm::vec3(x, y, z));
}

//	Setters & Getters

auto Node::getMesh() -> MeshPtr{
	return mesh_;
}

void Node::setMesh(const MeshPtr& mesh) {
	mesh_ = mesh;
}

const glm::mat4& Node::getTransform() const {
	return transform_;
}

void Node::setTransform(const glm::mat4& transform) {
	transform_ = transform;
}

void Node::addChild(NodePtr node) {
	nodes_.push_back(node);
}

auto Node::getChildren() -> NodeList& {
	return nodes_;
}
