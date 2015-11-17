#include "raytracer_system.h"

#include "vector3.h"
#include "ray.h"
#include "ray_hit.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "collisions/collisions.h"

#include "renderer/texture.h"

#include "material.h"
#include "shading/lambert_shader.h"
#include "voxels/voxel_model.h"
#include "lightning/directional_light.h"
#include "core/mt/task.h"







class PixelColorTask : public Lumix::MT::Task
{
public:
	PixelColorTask(Lumix::IAllocator& allocator)
		: Lumix::MT::Task(allocator)
	{
	}


	~PixelColorTask() {}


	int task()
	{
		while (true)
		{
			//calculate color of pixel by shotted ray
		}
		return 0;
	}

	void stop() { }
};










namespace LumixRayTracer
{

RayTracerSystem::RayTracerSystem(Lumix::IAllocator& allocator)
	: _allocator(allocator)
{
	ColorSampler* sampAmb = LUMIX_NEW(_allocator, ColorSampler)(Vector3(0.05f, 0.05f, 0.05f));
	ColorSampler* sampDiff = LUMIX_NEW(_allocator, ColorSampler)(Vector3(1.0f, 1.0f, 1.0f));
	LambertShader* shad = LUMIX_NEW(_allocator, LambertShader)(sampAmb, sampDiff);
	_objectMaterial = LUMIX_NEW(_allocator, Material)(shad);

	_voxelWord = LUMIX_NEW(_allocator, VoxelModel)(10, 10, 10);
	_voxelWord->ObjMaterial = _objectMaterial;

	_light = LUMIX_NEW(_allocator, DirectionalLight)(Vector3(-1, -1, -1));
}

RayTracerSystem::~RayTracerSystem()
{
	LambertShader* sh = static_cast<LambertShader*>(_objectMaterial->MaterialShader);
	LUMIX_DELETE(_allocator, sh->AmbientSampler);
	LUMIX_DELETE(_allocator, sh->DiffuseSampler);
	LUMIX_DELETE(_allocator, _objectMaterial->MaterialShader);
	LUMIX_DELETE(_allocator, _objectMaterial);
	LUMIX_DELETE(_allocator, _light);
}

void RayTracerSystem::SetTexture(Lumix::Texture* texture)
{
	_texture = texture;
}

void RayTracerSystem::Update(const float &deltaTime)
{
	if (!_isReady)
		return;

	ASSERT(_texture->getBytesPerPixel() == 4);
	int width = _texture->getWidth();
	int height = _texture->getHeight();
	uint32_t* data = (uint32_t*)(_texture->getData());

	Ray ray;
	RayHit intersection;
	
	float deltaX = 1.0f / width;
	float deltaY = 1.0f / height;
	float relX = 0.0f;
	float relY = 1.0f;

	int index = 0;

	for (int y = 0; y < height; ++y)
	{
		relX = 0.0f;
		index = y * height;
		for (int x = 0; x < width; ++x)
		{
			_camera.GetRay(relX, relY, ray);
			if (Intersections::RayAndVoxelGrid(ray, *_voxelWord, intersection))
			{
				Vector3 color = intersection.HitObject->ObjMaterial->MaterialShader->GetColor(intersection.Position, intersection.Normal, _camera, *_light);
				uint8_t tmp[4] = { (uint8_t)(color.x * 255), (uint8_t)(color.y * 255), (uint8_t)(color.z * 255), 0xFF };
				data[index] = *(uint32_t*)(tmp);
			}
			else
			{
				uint8_t tmp[4] = { (uint8_t)(Math::Abs(ray.Direction.x) * 100), (uint8_t)(Math::Abs(ray.Direction.y) * 100), (uint8_t)(Math::Abs(ray.Direction.z) * 100), 0xFF };
				data[index] = *(uint32_t*)(tmp);
			}

			++index;
			relX += deltaX;
		}
		relY -= deltaY;
	}
	_texture->onDataUpdated(0, 0, width, height);
}

void RayTracerSystem::UpdateCamera(const Lumix::Vec3 &position,
	const Lumix::Quat &rotation,
	const float &fov,
	const float &width,
	const float &height,
	const float &nearPlane,
	const float &farPlane,
	const Lumix::Matrix& viewMatrix)
{
	_camera.Position = position;
	_camera.Rotation = rotation;
	_camera.FOV = fov;
	_camera.Width = width;
	_camera.Height = height;
	_camera.NearPlane = nearPlane;
	_camera.FarPlane = farPlane;
	_camera.OnChanged();
}

} // ~namespace LumixRayTracer
