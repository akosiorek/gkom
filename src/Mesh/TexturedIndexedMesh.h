#ifndef TEXTURED_INDEXED_MESH_H
#define TEXTURED_INDEXED_MESH_H

#include "IMesh.h"
#include <memory>

class Texture;
class TexturedTechnique;

class TexturedIndexedMesh : public IMesh {
	typedef std::shared_ptr<Texture> TexturePtr;
	typedef std::shared_ptr<TexturedTechnique> TechniquePtr;
public:
	TexturedIndexedMesh(const std::vector<float>& geometry, const std::vector<float>& normals,
			const std::vector<float> texCoords, const std::vector<uint>& indices, GLuint drawMode = GL_TRIANGLES);

	virtual void setView(const glm::mat4& view) override;
	virtual void draw() override;

	virtual void setNormalTransform(const glm::mat3 normalTransform);
	void setTexture(TexturePtr texture);
	TexturePtr getTexture();

	void setTechnique(TechniquePtr technique);
	void setTextureUnit(GLuint textureUnit);

private:
	GLuint viewUniform_;
	GLuint normalUniform_;
	GLuint samplerUniform_;
	GLuint vao_;

	std::vector<float> texCoords_;
	std::vector<float> normals_;
	std::vector<uint> indices_;
	TexturePtr texture_;
	TechniquePtr technique_;
};

#endif // TEXTURED_INDEXED_MESH_H
