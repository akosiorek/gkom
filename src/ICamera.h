/*
 * ICamera.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef ICAMERA_H_
#define ICAMERA_H_

#include "Movable.h"

#include "glm/glm.hpp"

class ICamera : public Movable {
public:
	ICamera() = default;
	virtual ~ICamera() = default;


	virtual void pointAt(float x, float y, float z) = 0;
	virtual void setFOV(float fov) = 0;
	virtual void setRatio(int width, int height) = 0;
	virtual void setDistance(float distance) = 0;
	virtual void setClipping(float near, float far) = 0;

	virtual const glm::mat4& getTransform() const = 0;
	virtual void setTransform(const glm::mat4& transform) = 0;

	virtual void scale(float x, float y, float z) override {};
};

#endif /* ICAMERA_H_ */
