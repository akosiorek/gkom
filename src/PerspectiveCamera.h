/*
 * PerspectiveCamera.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef PERSPECTIVECAMERA_H_
#define PERSPECTIVECAMERA_H_

#include "ICamera.h"

class PerspectiveCamera: public ICamera {
public:
	PerspectiveCamera();
	virtual ~PerspectiveCamera() = default;

	virtual void translate(float x, float y = 0, float z = 0) override;
	virtual void rotate(Axis axis, float deg) override;

	virtual void pointAt(float x, float y, float z) override;
	virtual void setFOV(float fov) override;
	virtual void setRatio(int width, int height) override;
	virtual void setDistance(float distance) override;
	virtual void setClipping(float near, float far) override;

	virtual const glm::mat4& getTransform() const override;
	virtual void setTransform(const glm::mat4& transform) override;

private:
	glm::mat4 transform_;
	float near_;
	float far_;
	float scale_;
	float ratio_;

	static const float degToRad_;
};

#endif /* PERSPECTIVECAMERA_H_ */
