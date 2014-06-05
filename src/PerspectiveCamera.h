/*
 * PerspectiveCamera.h
 *
 *  Created on: 22 May 2014
 *      Author: Adam Kosiorek
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
	void updateView();
	void updateProjection();
	void updateTransform() const ;

private:
	float ratio_;
	float fov_;
	float near_;
	float far_;
	glm::vec3 position_;
	glm::vec3 target_;
	glm::vec3 up_;
	glm::mat4 rotation_;
	glm::mat4 projection_;
	glm::mat4 view_;
	glm::mat4 model_;
	mutable glm::mat4 transform_;
	mutable bool outdated_;

	static const float degToRad_;
};

#endif /* PERSPECTIVECAMERA_H_ */
