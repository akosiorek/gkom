/*
 * Utils.h
 *
 *  Created on: 22 May 2014
 *      Author: Adam Kosiorek
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

class Utils {
public:
	Utils() = delete;
	virtual ~Utils() = delete;

	static GLuint loadShader(GLenum eShaderType, const std::string &strShaderFilename);
	static GLuint createProgram(const std::vector<GLuint> &shaderList);

	template <typename T>
	static T str2num(const std::string& str, const T defaultValue = T());
	static std::vector<float> loadVertexData(const std::string& filename);
	static std::string loadFile(const std::string& filepath);
	static GLuint genBuffer(GLenum bufferType, GLenum drawType, const std::vector<float>& data);
	static double elapsedSinceLastFrame();
	static void setAmbientLightIntensity(const glm::vec4& light);
	static void setDiffuseLightIntensity(const glm::vec4& light);
	static void setDiffuseLightDir(const glm::vec3& light);
	static glm::vec3 getDiffuseLightDir();
	static cv::Mat loadImage(const std::string& filename);

	template<typename T>
	static void dumpVec(const std::vector<T>& vec, const std::string& logfile) {

		std::ofstream of(logfile);
		for(int i = 0; i < vec.size(); ++i) {
			of << vec[i] << " ";
			if(i % 100 == 0)
				of << std::endl;
		}
	}

private:
	static GLuint createShader(GLenum shaderType, const std::string& strShaderFile);

	static const std::string shaderPrefix_;
	static const std::string dataPrefix_;
	static glm::vec3 diffuseLightDir_;
};

#endif /* UTILS_H_ */
