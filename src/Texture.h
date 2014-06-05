/*
 * Texture.h
 *
 *  Created on: 22 May 2014
 *      Author: Adam Kosiorek
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

#include <opencv2/core/core.hpp>
#include <GL/glew.h>

class Texture {
public:
	Texture(GLenum textureTarget, const std::string& fileName);

	void load();
	void bind(GLenum textureUnit);

private:
	std::string filename_;
	cv::Mat mat_;

	GLenum textureTarget_;
	GLuint textureObj_;
};

#endif /* TEXTURE_H_ */
