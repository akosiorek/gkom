/*
 * PlaneGenerator.h
 *
 *  Created on: May 24, 2014
 *      Author: Adam Kosiorek Kosiorek
 */

#ifndef PLANEGENERATOR_H_
#define PLANEGENERATOR_H_

#include "glm/glm.hpp"
#include <vector>

class PlaneGenerator {
public:
	PlaneGenerator() = default;
	virtual ~PlaneGenerator() = default;

	void generate(int width, int height, int noise = 0);
	void displace(int x, int y, float dx, float dy, float dz);


	const std::vector<unsigned>& getIndices() const;
	const std::vector<float>& getVertices() const;
	const std::vector<float>& getNormals() const;
	const std::vector<float>& getTextureCoords() const;

private:
	std::vector<unsigned> genIndices(int width, int height) const;
	std::vector<float> genVertices(int width, int height, int noise = 0) const;
	std::vector<float> genNormals(int width, int height) const;
	glm::vec3 getVert(unsigned v) const;
	std::vector<float> genTextureCoords(int width, int height) const;


	std::vector<float> vertices_;
	std::vector<unsigned> indices_;
	std::vector<float> normals_;
	std::vector<float> textureCoords_;
};

#endif /* PLANEGENERATOR_H_ */
