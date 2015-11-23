#pragma once

namespace Lumix
{
struct Vec3;
struct Quat;
struct Matrix;
class Texture;
class IAllocator;
}

namespace LumixRayTracer
{
class Material;
class VoxelModel;
class Camera;
class DirectionalLight;


class RayTracerSystem
{
public:
	RayTracerSystem() { }
	virtual ~RayTracerSystem() { }

	static RayTracerSystem* create(Lumix::IAllocator& allocator);
	static void destroy(RayTracerSystem& culling_system);

	virtual void SetTexture(Lumix::Texture* texture) = 0;

	virtual void Update(const float &deltaTime) = 0;

	virtual Camera& GetCamera() = 0;

	virtual inline void SetIsReady(bool isReady) = 0;
	virtual inline bool GetIsReady() const = 0;
};

} // ~ namespace LumixRayTracer
