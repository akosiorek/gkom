/*

 Copyright 2011 Etay Meiri

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SkyboxTechnique.h"

#include <glm/gtc/type_ptr.hpp>

#include <limits>
#include <string>

SkyboxTechnique::SkyboxTechnique() {

	shaderProg_ =createProgram({
			loadShader(GL_VERTEX_SHADER, "skybox.vs"),
			loadShader(GL_FRAGMENT_SHADER, "skybox.fs")
	});

	WVPLocation_ = getUniformLocation("gWVP");
	textureLocation_ = getUniformLocation("gCubemapTexture");
}

void SkyboxTechnique::setWVP(const glm::mat4& wvp) {
	glUniformMatrix4fv(WVPLocation_, 1, GL_TRUE, glm::value_ptr(wvp));
}

void SkyboxTechnique::setTextureUnit(unsigned int textureUnit) {
	glUniform1i(textureLocation_, textureUnit);
}

