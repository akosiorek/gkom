#ifndef TEXTURED_TECHNIQUE_H
#define TEXTURED_TECHNIQUE_H

#include "Technique.h"
#include "glm/glm.hpp"

class TexturedTechnique : public Technique {
public:
	TexturedTechnique();

	void setWVP(const glm::mat4& wvp);
	void setTextureUnit(unsigned int textureUnit);
	void setAmbientIntensity(const glm::vec4& intensity);
	void setDiffuseIntensity(const glm::vec4& intensity);
	void setDiffuseDir(const glm::vec3& dir);

private:
	GLuint wvpLoc_;
	GLuint textureLoc_;
	GLuint ambientIntensityLoc_;
	GLuint diffuseIntensityLoc_;
	GLuint diffuseDirLoc_;
};


#endif // TEXTURED_TECHNIQUE_H
