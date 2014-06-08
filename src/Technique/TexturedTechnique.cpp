#include "TexturedTechnique.h"
#include <glm/gtc/type_ptr.hpp>

TexturedTechnique::TexturedTechnique() {

	shaderProg_ = createProgram({
			loadShader(GL_VERTEX_SHADER, "texture2d.vs"),
			loadShader(GL_FRAGMENT_SHADER, "texture2d.fs")
	});

	wvpLoc_ = getUniformLocation("gWVP");
	textureLoc_ = getUniformLocation("gSampler");
	ambientIntensityLoc_ = getUniformLocation("ambientLightIntensity");
	diffuseIntensityLoc_ = getUniformLocation("diffuseLightIntensity");
	diffuseDirLoc_ = getUniformLocation("dirToLight");

}

void TexturedTechnique::setWVP(const glm::mat4& wvp) {
	glUniformMatrix4fv(wvpLoc_, 1, GL_FALSE, glm::value_ptr(wvp));
}

void TexturedTechnique::setTextureUnit(unsigned int textureUnit) {
	glUniform1i(textureLoc_, textureUnit);
}

void TexturedTechnique::setAmbientIntensity(const glm::vec4& intensity) {
	glUniform4fv(ambientIntensityLoc_, 1, glm::value_ptr(intensity));
}

void TexturedTechnique::setDiffuseIntensity(const glm::vec4& intensity) {
	glUniform4fv(diffuseIntensityLoc_, 1, glm::value_ptr(intensity));
}

void TexturedTechnique::setDiffuseDir(const glm::vec3& dir) {
	glUniform3fv(diffuseDirLoc_, 1, glm::value_ptr(dir));
}