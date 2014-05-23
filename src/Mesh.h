/*
 * Mesh.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef MESH_H_
#define MESH_H_

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <memory>
#include <vector>

class Mesh {
public:
	Mesh(const std::vector<float>& geom, const std::vector<float>& colour);
	virtual ~Mesh() = default;

	void setView(const glm::mat4& view);
	void draw();


	const std::vector<float>& getColours() const;
	void setColours(const std::vector<float>& colours);
	const std::vector<float>& getGeometry() const;
	void setGeometry(const std::vector<float>& geometry);
	GLuint getProgram() const;
	void setProgram(GLuint program);
	const std::string& getViewName() const;
	void setViewName(const std::string& viewName);

private:
	std::vector<float> geometry_;
	std::vector<float> colours_;
	GLuint program_;
	GLuint viewUniform_;
	GLuint vao_;
	std::string viewName_;
};

#endif /* MESH_H_ */
