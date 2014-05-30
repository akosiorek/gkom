/*
 * Texture.cpp
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#include "Texture.h"
#include "Utils.h"

#include <opencv2/highgui/highgui.hpp>

Texture::Texture(GLenum textureTarget, const std::string& fileName)
	: textureTarget_(textureTarget), filename_(fileName) {}

void Texture::load() {

	mat_ = cv::imread(filename_, 1);
	if(!mat_.data) {
		Utils::throwRuntime("Couldn't load image: " + filename_);
	}

	glGenTextures(1, &textureObj_);
	glBindTexture(textureTarget_, textureObj_);
	glTexImage2D(textureTarget_, 0, GL_RGBA, mat_.cols,
			mat_.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, mat_.data);

	glTexParameterf(textureTarget_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(textureTarget_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::bind(GLenum textureUnit) {
	glActiveTexture(textureUnit);
	glBindTexture(textureTarget_, textureObj_);
}
