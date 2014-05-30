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

#ifndef TECHNIQUE_H
#define	TECHNIQUE_H

#include <GL/glew.h>

#include <string>
#include <vector>

#define INVALID_UNIFORM_LOCATION 0xffffffff

class Technique {
public:
	Technique();
	virtual ~Technique();

	void enable();

protected:
	GLint getUniformLocation(const std::string& pUniformName);
	GLint getProgramParam(GLint param);
	GLuint createProgram(const std::vector<GLuint> &shaderList);
	GLuint loadShader(GLenum eShaderType, const std::string &strShaderFilename);

	GLuint shaderProg_;

private:
	GLuint createShader(GLenum shaderType, const std::string& strShaderFile);

	static const std::string shaderPrefix_;
};

#endif	/* TECHNIQUE_H */

