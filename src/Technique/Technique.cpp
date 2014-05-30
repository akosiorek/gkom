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

const std::string Technique::shaderPrefix_ = "../src/shaders/";

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

GLuint Technique::createShader(GLenum shaderType, const std::string &strShaderFile) {

	GLuint shader = glCreateShader(shaderType);
	const char *strFileData = strShaderFile.c_str();
	glShaderSource(shader, 1, &strFileData, NULL);

	glCompileShader(shader);

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		const char *strShaderType = NULL;
		switch (shaderType) {
		case GL_VERTEX_SHADER:
			strShaderType = "vertex";
			break;
		case GL_GEOMETRY_SHADER:
			strShaderType = "geometry";
			break;
		case GL_FRAGMENT_SHADER:
			strShaderType = "fragment";
			break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", strShaderType,
				strInfoLog);
		delete[] strInfoLog;
	}

	return shader;
}

GLuint Technique::loadShader(GLenum shaderType, const std::string& shaderFilename) {

	std::string shaderData = Utils::loadFile(shaderPrefix_ + shaderFilename);
	return createShader(shaderType, shaderData);
}

GLuint Technique::createProgram(const std::vector<GLuint> &shaderList) {

	GLuint program = glCreateProgram();
	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	for (size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glDetachShader(program, shaderList[iLoop]);

	return program;
}
