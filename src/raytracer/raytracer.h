#pragma once


#include "lumix.h"
#include "camera.h"

namespace LumixRayTracer
{

class RayTracer
{
private:
	Camera camera;

public:
	virtual void Update(const float &deltaTime);
	virtual void UpdateCamera(const Lumix::Vec3 &position,
		const Lumix::Quat &rotation,
		const float &fov,
		const float &width,
		const float &height,
		const float &nearPlane,
		const float &farPlane,
		const Lumix::Matrix& viewMatrix);
};

} // ~ namespace LumixRayTracer
