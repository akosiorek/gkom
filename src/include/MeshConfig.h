/*
 * MeshConfig.h
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek
 */

#ifndef MESHCONFIG_H_
#define MESHCONFIG_H_

#include <string>

struct MeshConfig {
public:
	MeshConfig() = delete;
	virtual ~MeshConfig() = delete;

	static unsigned COLORED_VERT_PROGRAM;
	static unsigned UNIFORM_COLOR_PROGRAM;
	static std::string PERSPECTIVE_UNIFORM_NAME;
	static std::string COLOUR_UNIFORM_NAME;
	static std::string NORMAL_UNIFORM_NAME;
	static std::string LIGHT_DIR_UNIFORM_NAME;
	static std::string DIFFUSE_LIGHT_UNIFORM_NAME;
	static std::string AMBIENT_LIGHT_UNIFORM_NAME;
};

#endif /* MESHCONFIG_H_ */
