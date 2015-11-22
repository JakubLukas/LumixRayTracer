#pragma once

#include "Debug/allocator.h"
#include "core/free_list.h"

#include "core/MTJD/manager.h"
#include "core/MTJD/job.h"

#include "camera.h"


namespace Lumix
{
class Texture;
}

namespace LumixRayTracer
{
class Material;
class VoxelModel;
class DirectionalLight;






//-----------------------------------------------------------------------------

class RayTracerSystem
{
public:
	RayTracerSystem() { }
	virtual ~RayTracerSystem() { }

	static RayTracerSystem* create(Lumix::IAllocator& allocator);
	static void destroy(RayTracerSystem& culling_system);

	virtual void SetTexture(Lumix::Texture* texture) = 0;

	virtual void Update(const float &deltaTime) = 0;
	virtual void UpdateCamera(const Lumix::Vec3 &position,
		const Lumix::Quat &rotation,
		const float &fov,
		const float &width,
		const float &height,
		const float &nearPlane,
		const float &farPlane,
		const Lumix::Matrix& viewMatrix) = 0;

	virtual inline void SetIsReady(bool isReady) = 0;
	virtual inline bool GetIsReady() const = 0;
};

} // ~ namespace LumixRayTracer
