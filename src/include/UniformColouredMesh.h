/*
 * Mesh.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef UniformColouredMesh_H_
#define UniformColouredMesh_H_

#include "IMesh.h"

class UniformColouredMesh : public IMesh {
public:
	UniformColouredMesh(const std::vector<float>& geom, const std::vector<float>& colour,
			const std::vector<unsigned>& indices = std::vector<unsigned>(), GLuint drawMode = GL_TRIANGLES);

	virtual ~UniformColouredMesh() = default;

	virtual void setView(const glm::mat4& view) override;
	virtual void setNormalTransform(const glm::mat3 normalTransform);

	virtual void draw() override;

	virtual void setNormals(const std::vector<float>& normals);

private:
	GLuint viewUniform_;
	GLuint colourUniform_;
	GLuint normalUniform_;
	GLuint vao_;
};

#endif /* UniformColouredMesh_H_ */