/*
 * IndexedMesh.h
 *
 *  Created on: Jun 6, 2014
 *      Author: Adam Kosiorek
 */

#ifndef INDEXEDMESH_H_
#define INDEXEDMESH_H_

#include "IMesh.h"

class IndexedMesh : public IMesh {
public:
	IndexedMesh(const std::vector<float>& geometry, const std::vector<float>& normals,
			const std::vector<uint>& indices, const glm::vec3& colour, GLuint drawMode = GL_TRIANGLES);

	virtual void setView(const glm::mat4& view) override;
	virtual void draw() override;

	virtual void setNormalTransform(const glm::mat3 normalTransform);
	void setColour(const glm::vec3& colour);

private:
	GLuint viewUniform_;
	GLuint colourUniform_;
	GLuint normalUniform_;
	GLuint vao_;

	std::vector<float> normals_;
	std::vector<uint> indices_;
	glm::vec3 colour_;
};

#endif /* INDEXEDMESH_H_ */
