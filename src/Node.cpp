/*
 * Node.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Node.h"
#include "Mesh.h"

#include <glm/gtc/matrix_transform.hpp>

Node::Node(MeshPtr mesh)
	: mesh_(mesh) {}


void Node::draw(const glm::mat4& transform) {

	traverse(shared_from_this(), transform);
}

void Node::traverse(NodePtr node, const glm::mat4& transform) {

	auto currentTransform = transform * transform_;
	if(mesh_) {
		mesh_->setView(currentTransform);
		mesh_->draw();
	}

	for(auto child : node->getChildren()) {
		traverse(child, currentTransform);
	}
}

void Node::translate(float x, float y, float z) {
	glm::translate(transform_, glm::vec3(x, y, z));
}

void Node::roate(Axis axis, float deg) {
	switch(axis) {
		case Axis::X: glm::rotate(transform_, deg, glm::vec3(1.0f, .0f, .0f)); break;
		case Axis::Y: glm::rotate(transform_, deg, glm::vec3(.0f, 1.0f, .0f)); break;
		case Axis::Z: glm::rotate(transform_, deg, glm::vec3(.0f, .0f, 1.0f)); break;
	}
}

void Node::scale(float x, float y, float z) {
	glm::scale(transform_, glm::vec3(x, y, z));
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
