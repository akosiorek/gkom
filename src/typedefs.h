/*
 * typedefs.h
 *
 *  Created on: 30 May 2014
 *      Author: Adam Kosiorek
 */

#ifndef TYPEDEFS_H_
#define TYPEDEFS_H_

#include <memory>

#define MakePtr(x, y, z) class x; typedef std::shared_ptr<x> y##z
#define DecPtr1(x) MakePtr(x, x, Ptr)
#define DecPtr2(x, y) MakePtr(x, y, Ptr)

#define MakeUPtr(x, y, z) class x; typedef std::unique_ptr<x> y##z
#define DecUPtr1(x) MakeUPtr(x, x, Ptr)
#define DecUPtr2(x, y) MakeUPtr(x, y, Ptr)


DecPtr1(Node);
DecPtr1(Texture);
DecPtr1(Box);
DecPtr1(Movable);
DecPtr1(Trajectory);

DecPtr2(ICamera, Camera);
DecPtr2(IMesh, Mesh);


DecUPtr2(IRenderer, Renderer);

#endif /* TYPEDEFS_H_ */

