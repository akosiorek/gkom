/*
 * SkyboxMesh.h
 *
 *  Created on: Jun 6, 2014
 *      Author: Adam Kosiorek
 */

#ifndef SKYBOXMESH_H_
#define SKYBOXMESH_H_

#include "IMesh.h"

#include "TexturedSkybox.h"
#include "SkyboxTechnique.h"

class SkyboxMesh : public IMesh {
public:
	SkyboxMesh(const std::string& dir, const std::vector<std::string>& names);

	virtual void setView(const glm::mat4& view);
	virtual void draw();

private:
	GLuint vao_;
	TexturedSkybox texturedSkybox_;
	SkyboxTechnique skyboxTechnique_;
};

#endif /* SKYBOXMESH_H_ */
