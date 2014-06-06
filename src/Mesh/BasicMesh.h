/*
 * Mesh.h
 *
 *  Created on: 22 May 2014
 *      Author: Adam Kosiorek
 */

#ifndef BasicMesh_H_
#define BasicMesh_H_

#include "IMesh.h"
#include <GL/glew.h>

class BasicMesh : public IMesh {
public:
	BasicMesh(const std::vector<float>& geometry, const std::vector<float>& normals,
			const glm::vec3& colour, GLuint drawMode = GL_TRIANGLES);

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
	glm::vec3 colour_;
};

#endif /* BasicMesh_H_ */
