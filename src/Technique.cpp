/*

 Copyright 2011 Etay Meiri

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Technique.h"
#include "Utils.h"

#define GLCheckError() (glGetError() == GL_NO_ERROR)

Technique::Technique() : shaderProg_(0) {}

Technique::~Technique() {

	if (shaderProg_ != 0) {
		glDeleteProgram(shaderProg_);
		shaderProg_ = 0;
	}
}

void Technique::enable() {
	glUseProgram(shaderProg_);
}

GLint Technique::getUniformLocation(const std::string& pUniformName) {
	GLuint Location = glGetUniformLocation(shaderProg_, pUniformName.c_str());

	if (Location == INVALID_UNIFORM_LOCATION) {
		Utils::throwRuntime("Unable to get the location of uniform " + pUniformName);
	}

	return Location;
}

GLint Technique::getProgramParam(GLint param) {
	GLint ret;
	glGetProgramiv(shaderProg_, param, &ret);
	return ret;
}
