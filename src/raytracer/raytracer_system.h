#pragma once

#include "Debug/allocator.h"

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

class RayTracerSystem
{
private:
	Lumix::Debug::Allocator _allocator;

	Camera _camera;
	Lumix::Texture* _texture;
	bool _isReady = false;

	Material* _objectMaterial;
	VoxelModel* _voxelWord;
	DirectionalLight* _light;

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

	inline void SetIsReady(bool isReady);
	inline bool GetIsReady();
};

inline void RayTracerSystem::SetIsReady(bool isReady)
{
	_isReady = isReady;
}

inline bool RayTracerSystem::GetIsReady()
{
	return _isReady;
}

} // ~ namespace LumixRayTracer
