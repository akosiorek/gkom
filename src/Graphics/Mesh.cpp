/*
 * UniformColouredMesh.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Mesh.h"
#include "Utils.h"


const std::string Mesh::vertexExt_ = ".vert";
const std::string Mesh::normalExt_= ".norm";
const std::string Mesh::textureExt_ = ".col";

Mesh::Mesh(const std::string& name) {
	if(name.size() != 0) {
		coords_ = Utils::loadVertexData(name + vertexExt_);
		normals_ = Utils::loadVertexData(name + normalExt_);
		texture_ = Utils::loadVertexData(name + textureExt_);
	}
}
