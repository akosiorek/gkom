

/*
 * TextuedSkybox.h
 *
 *  Created on: 30 May 2014
 *      Author: adam
 */

#ifndef TEXTUEDSKYBOX_H_
#define TEXTUEDSKYBOX_H_

#include <vector>
#include <string>

#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

class TexturedSkybox {
public:

	/**
	 * names = {+x, -x, +y, -z, +z, -z}
	 */
	TexturedSkybox(const std::string& dir, const std::vector<std::string>& names);
	virtual ~TexturedSkybox();

    bool load();
    void bind(GLenum TextureUnit);

private:

    const std::string& dir_;
    const std::vector<std::string>& fileNames_;
    GLuint textureObj_;
};

#endif /* TEXTUEDSKYBOX_H_ */
