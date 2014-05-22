/*
 * Utils.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Utils.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

const std::string Utils::shaderPrefix_ = "../src/shaders/";
const std::string Utils::dataPrefix_ = "../src/data/";

GLuint Utils::loadShader(GLenum shaderType, const std::string& shaderFilename) {

	std::ifstream shaderFile(shaderPrefix_ + shaderFilename);
	std::stringstream shaderData;
	shaderData << shaderFile.rdbuf();
	shaderFile.close();

	const char* shaderDataPtr = shaderData.str().c_str();

	GLuint shader = glCreateShader(shaderType);
	glShaderSource (shader, 1, &shaderDataPtr, NULL);
	glCompileShader (shader);

	// check for compile errors
	int params = -1;
	glGetShaderiv (shader, GL_COMPILE_STATUS, &params);
	if (GL_TRUE != params) {
	  throw std::runtime_error("Couldn't compile shader " + shaderFilename);
	}

	return shader;
}

GLuint Utils::createProgram(const std::vector<GLuint> &shaderList) {
		GLuint program =  glCreateProgram ();

		for(auto shader : shaderList) {
			glAttachShader(program, shader);
		}
		glLinkProgram (program);

		int params = -1;
		glGetProgramiv (program, GL_LINK_STATUS, &params);
		if (GL_TRUE != params) {
			throw std::runtime_error("could not link shader programme");
		}

		return program;
}

template <typename T>
T Utils::str2num(const std::string& str, const T defaultValue) {

	std::stringstream ss(str);
	T t;
	if(ss >> t) {
		return t;
	}
	return defaultValue;
}

std::vector<float> Utils::loadVertexData(const std::string& filename) {

	std::ifstream input(dataPrefix_ + filename);
	std::string line;
	std::vector<float> data;

	while(std::getline(input, line, ',')) {

		data.push_back(str2num<float>(line));
	}

	return data;
}
