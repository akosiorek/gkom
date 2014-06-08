/*
 * MeshConfig.cpp
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#include "MeshConfig.h"

unsigned MeshConfig::COLORED_VERT_PROGRAM = 0;
unsigned MeshConfig::UNIFORM_COLOR_PROGRAM = 0;

std::string MeshConfig::PERSPECTIVE_UNIFORM_NAME = "perspectiveMatrix";
std::string MeshConfig::COLOUR_UNIFORM_NAME = "baseColour";
std::string MeshConfig::NORMAL_UNIFORM_NAME = "normalMatrix";
std::string MeshConfig::LIGHT_DIR_UNIFORM_NAME = "dirToLight";
std::string MeshConfig::DIFFUSE_LIGHT_UNIFORM_NAME = "diffuseLightIntensity";
std::string MeshConfig::AMBIENT_LIGHT_UNIFORM_NAME = "ambientLightIntensity";


