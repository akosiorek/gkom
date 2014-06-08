/*
 * Utils.cpp
 *
 *  Created on: 22 May 2014
 *      Author: Adam Kosiorek
 */

#include "Utils.h"
#include "MeshConfig.h"
#include "Logger.h"

#include <glm/gtc/type_ptr.hpp>

 #include <opencv2/imgproc/imgproc.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

const std::string Utils::shaderPrefix_ = "../src/shaders/";
const std::string Utils::dataPrefix_ = "../src/data/";
glm::vec3 Utils::diffuseLightDir_ = glm::vec3(1.0f, 1.0f, 1.0f);

GLuint Utils::createShader(GLenum shaderType, const std::string &strShaderFile) {

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

std::string Utils::loadFile(const std::string& filepath) {

	std::ifstream file(filepath);
	std::stringstream sstream;
	sstream << file.rdbuf();
	file.close();
	return sstream.str();
}

GLuint Utils::loadShader(GLenum shaderType, const std::string& shaderFilename) {

	std::string shaderData = loadFile(shaderPrefix_ + shaderFilename);
	return createShader(shaderType, shaderData);
}

GLuint Utils::createProgram(const std::vector<GLuint> &shaderList) {

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

GLuint Utils::genBuffer(GLenum bufferType, GLenum drawType, const std::vector<float>& data) {

	GLuint vertexBuffer = 0;
	glGenBuffers (1, &vertexBuffer);
	glBindBuffer (bufferType, vertexBuffer);
	glBufferData (bufferType, data.size() * sizeof(float), data.data(), drawType);
	return vertexBuffer;
}

double Utils::elapsedSinceLastFrame() {

	static double lastTime = glfwGetTime();
	double thisTime = glfwGetTime();
	double elapsed = thisTime - lastTime;
	lastTime = thisTime;
	return elapsed;
}

void Utils::setAmbientLightIntensity(const glm::vec4& light) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniform4fv(
			glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::AMBIENT_LIGHT_UNIFORM_NAME.c_str()),
			1, glm::value_ptr(light));
	glUseProgram(0);

}

void Utils::setDiffuseLightIntensity(const glm::vec4& light) {

	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniform4fv(
			glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::DIFFUSE_LIGHT_UNIFORM_NAME.c_str()),
			1, glm::value_ptr(light));
	glUseProgram(0);

}

void Utils::setDiffuseLightDir(const glm::vec3& light) {

	diffuseLightDir_ = light;
	glUseProgram(MeshConfig::UNIFORM_COLOR_PROGRAM);
	glUniform3fv(
			glGetUniformLocation(MeshConfig::UNIFORM_COLOR_PROGRAM, MeshConfig::LIGHT_DIR_UNIFORM_NAME.c_str()),
			1, glm::value_ptr(diffuseLightDir_));
	glUseProgram(0);

}

glm::vec3 Utils::getDiffuseLightDir() {
	return diffuseLightDir_;
}

cv::Mat Utils::loadImage(const std::string& filename) {

	cv::Mat mat = cv::imread(filename, CV_LOAD_IMAGE_COLOR);
	if(!mat.data) {
		RUNTIME_ERR("Couldn't load image: " + filename);
	}

	//	Convert to [0, 1] float and RGBA
	cv::cvtColor(mat, mat, CV_BGR2RGBA, 4);
	// mat.convertTo(mat, CV_32F, 1/255.f);
	return mat;
}