/*
 * IRenderer.h
 *
 *  Created on: 22 May 2014
 *      Author: adam
 */

#ifndef IRENDERER_H_
#define IRENDERER_H_

#include "typedefs.h"

class IRenderer {
protected:

public:
	IRenderer() = default;
	virtual ~IRenderer() = default;

	virtual void render(NodePtr node) = 0;
	virtual void clearScreen() = 0;
	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void setCamera(CameraPtr camera) = 0;
	virtual CameraPtr getCamera() = 0;

	virtual bool shouldClose() = 0;
};

#endif /* IRENDERER_H_ */
