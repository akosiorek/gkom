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
	void setIndices(const std::vector<unsigned>& indices);
	const std::vector<float>& getVertices() const;
	void setVertices(const std::vector<float>& vertices);
	const std::vector<float>& getNormals() const;
	void setNormals(const std::vector<float>& normals);

private:
	std::vector<unsigned> genIndices(int width, int height) const ;
	std::vector<float> genVertices(int width, int height, int noise = 0) const;
	std::vector<float> genNormals(int width, int height) const;
	glm::vec3 getVert(unsigned v) const;


	std::vector<float> vertices_;
	std::vector<unsigned> indices_;
	std::vector<float> normals_;
};

#endif /* PLANEGENERATOR_H_ */
