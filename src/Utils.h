/*
 * Utils.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

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


private:
	static GLuint createShader(GLenum shaderType, const std::string& strShaderFile);

	static const std::string shaderPrefix_;
	static const std::string dataPrefix_;
};

#endif /* UTILS_H_ */
