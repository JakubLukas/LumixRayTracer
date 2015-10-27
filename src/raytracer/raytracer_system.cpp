#include "raytracer_system.h"

#include "vector3.h"
#include "ray.h"
#include "ray_hit.h"
#include "primitives/sphere.h"
#include "collisions/collisions.h"

#include "renderer/texture.h"

#include "material.h"
#include "shading/phong_shader.h"


namespace LumixRayTracer
{

RayTracerSystem::RayTracerSystem(Lumix::IAllocator& allocator)
	: m_material_manager(allocator)
{

}

RayTracerSystem::~RayTracerSystem()
{

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

	Sphere s(Vector3(0.0f, 0.0f, -2.0f), 1.2f);
	Shader* shad = new PhongShader();
	Material* mat = new Material(shad);
	s.ObjMaterial = mat;


	Ray ray(Vector3(0, 0, 0), Vector3(0, 0, 1));
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
			camera.GetRay(relX, relY, ray);
			if (Intersections::RayAndSphere(ray, s, intersection))
			{
				data[index] = 0xFFFFFFFF;
				Vector3 color = intersection.HitObject->ObjMaterial->MaterialShader->GetColor(intersection.Position, intersection.Normal, camera.Position, camera.Position);
				uint8_t tmp[4] = { (uint8_t)(color.x * 255), (uint8_t)(color.y * 255), (uint8_t)(color.z * 255), 0xFF };
				data[index] = *(uint32_t*)(tmp);
			}
			else
			{
				uint8_t tmp[4] = { (uint8_t)(Math::Abs(ray.Direction.x) * 255), (uint8_t)(Math::Abs(ray.Direction.y) * 255), (uint8_t)(Math::Abs(ray.Direction.z) * 255), 0xFF };
				data[index] = *(uint32_t*)(tmp);
			}
			

			++index;
			relX += deltaX;
		}
		relY -= deltaY;
	}
	_texture->onDataUpdated(0, 0, width, height);

	//TODO get rid of this bullshit
	delete shad;
	delete mat;
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
	camera.Position = position;
	camera.Rotation = rotation;
	camera.FOV = fov;
	camera.Width = width;
	camera.Height = height;
	camera.NearPlane = nearPlane;
	camera.FarPlane = farPlane;
	camera.OnChanged();
}

void RayTracerSystem::SetIsReady(bool isReady)
{
	_isReady = isReady;
}

bool RayTracerSystem::GetIsReady()
{
	return _isReady;
}

} // ~namespace LumixRayTracer
