/*
 * TextuedSkybox.cpp
 *
 *  Created on: 30 May 2014
 *      Author: adam
 */

#include "TexturedSkybox.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

static const GLenum types[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                                  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                                  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

TexturedSkybox::TexturedSkybox(const std::string& dir, const std::vector<std::string>& names)
	: dir_(dir), fileNames_(names), textureObj_(0) {}

TexturedSkybox::~TexturedSkybox() {

	if (textureObj_ != 0) {
	        glDeleteTextures(1, &textureObj_);
	    }
}

bool TexturedSkybox::load()
{
    glGenTextures(1, &textureObj_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj_);


    for (unsigned int i = 0 ; i < 6 ; i++) {
        cv::Mat texture = cv::imread(dir_ + "/" + fileNames_[i], 1);

        glTexImage2D(types[i], 0, GL_RGB, texture.cols, texture.rows, 0,
        		GL_RGBA, GL_UNSIGNED_BYTE, texture.data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return true;
}

void TexturedSkybox::bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureObj_);
}
