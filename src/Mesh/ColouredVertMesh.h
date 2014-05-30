/*
 * Mesh.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef ColouredVertMesh_H_
#define ColouredVertMesh_H_

#include "IMesh.h"

class ColouredVertMesh : public IMesh {
public:
	ColouredVertMesh(const std::vector<float>& geom, const std::vector<float>& colour,
			const std::vector<unsigned>& indices = std::vector<unsigned>(), GLuint drawMode = GL_TRIANGLES);

	virtual ~ColouredVertMesh() = default;

	virtual void setView(const glm::mat4& view) override;
	virtual void draw() override;

private:
	GLuint viewUniform_;
	GLuint vao_;
};

#endif /* ColouredVertMesh_H_ */
