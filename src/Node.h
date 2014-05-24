/*
 * Node.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef NODE_H_
#define NODE_H_

#include "Movable.h"

#include <glm/glm.hpp>

#include <memory>
#include <list>

class IMesh;

class Node : public Movable {
	typedef std::shared_ptr<IMesh> MeshPtr;
	typedef std::shared_ptr<Node> NodePtr;
	typedef std::list<NodePtr> NodeList;

public:
	Node(MeshPtr mesh = nullptr);
	virtual ~Node() = default;

	void draw(const glm::mat4& transform = glm::mat4(1.0f));

	virtual void translate(float x, float y = 0, float z = 0) override;
	virtual void rotate(Axis axis, float deg) override;
	virtual void scale(float x, float y = 0, float z = 0) override;

	void addChild(NodePtr node = nullptr);
	NodeList& getChildren();

	MeshPtr getMesh();
	void setMesh(const MeshPtr& mesh);
	const glm::mat4& getTransform() const;
	void setTransform(const glm::mat4& transform);

private:
	NodeList nodes_;
	MeshPtr mesh_;
	glm::mat4 transform_;
};

#endif /* NODE_H_ */
