#pragma once

#include "lumix.h"
#include "core/iallocator.h"
#include "renderer/material_manager.h"

#include "camera.h"


namespace Lumix
{
class Texture;
}

namespace LumixRayTracer
{

class RayTracerSystem
{
private:
	Lumix::MaterialManager m_material_manager;

	Camera camera;
	Lumix::Texture* _texture;
	bool _isReady = false;

public:
	RayTracerSystem(Lumix::IAllocator& allocator);
	~RayTracerSystem();

	void SetTexture(Lumix::Texture* texture);

	void Update(const float &deltaTime);
	void UpdateCamera(const Lumix::Vec3 &position,
										const Lumix::Quat &rotation,
										const float &fov,
										const float &width,
										const float &height,
										const float &nearPlane,
										const float &farPlane,
										const Lumix::Matrix& viewMatrix);

	void SetIsReady(bool isReady);
	bool GetIsReady();
};

} // ~ namespace LumixRayTracer
