/*
 * Mesh.h
 *
 *  Created on: 30 May 2014
 *      Author: adam
 */

#ifndef MESH_H_
#define MESH_H_

#include <string>
#include <vector>

#include <GL/glew.h>

class Mesh {
public:
	Mesh(const std::string& name = std::string());
	virtual ~Mesh() = default;

private:
	std::vector<float> coords_;
	std::vector<float> normals_;
	std::vector<float> texture_;

	GLuint vao_;

	static const std::string vertexExt_;
	static const std::string normalExt_;
	static const std::string textureExt_;

};


#endif /* MESH_H_ */
