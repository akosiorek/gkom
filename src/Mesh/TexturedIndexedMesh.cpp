#include "TexturedIndexedMesh.h"
#include "Utils.h"
#include "MeshConfig.h"
#include "Texture.h"
#include "TexturedTechnique.h"

#include <glm/gtc/type_ptr.hpp>

TexturedIndexedMesh::TexturedIndexedMesh(const std::vector<float>& geometry, const std::vector<float>& normals,
			const std::vector<float> texCoords, const std::vector<uint>& indices, GLuint drawMode)
	: IMesh(geometry, drawMode), normals_(normals), texCoords_(texCoords), indices_(indices) {


	GLuint geomVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, geometry_);
	GLuint normalVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, normals_);
	GLuint texVBO = Utils::genBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, texCoords_);

	glGenVertexArrays (1, &vao_);
	glBindVertexArray (vao_);
	glEnableVertexAttribArray (0);
	glBindBuffer (GL_ARRAY_BUFFER, geomVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (1);
	glBindBuffer (GL_ARRAY_BUFFER, normalVBO);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray (2);
	glBindBuffer (GL_ARRAY_BUFFER, texVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
}

void TexturedIndexedMesh::setView(const glm::mat4& view) {

	technique_->enable();
	technique_->setWVP(view);
}

void TexturedIndexedMesh::setNormalTransform(const glm::mat3 normalTransform) {

}

void TexturedIndexedMesh::draw() {

	technique_->enable();
	glBindVertexArray (vao_);
	texture_->bind(GL_TEXTURE0);
	glDrawElements(drawMode_, indices_.size(), GL_UNSIGNED_INT, indices_.data());
	glUseProgram (0);
}

void TexturedIndexedMesh::setTexture(TexturePtr texture) {
	texture_ = texture;
}

auto TexturedIndexedMesh::getTexture() -> TexturePtr {
	return texture_;
}

void TexturedIndexedMesh::setTechnique(TechniquePtr technique) {
	technique_ = technique;
}

void TexturedIndexedMesh::setTextureUnit(GLuint textureUnit) {
	technique_->setTextureUnit(textureUnit);
}

