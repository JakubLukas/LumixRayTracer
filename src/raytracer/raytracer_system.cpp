#include "raytracer_system.h"

#include "vector3.h"
#include "ray.h"
#include "sphere.h"
#include "collisions.h"

#include "renderer/texture.h"


namespace LumixRayTracer
{

RayTracerSystem::RayTracerSystem()
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

	int bpp = _texture->getBytesPerPixel();

	Sphere s(Vector3(0.0f, 0.0f, -2.0f), 0.2f);
	Ray ray(Vector3(0, 0, 10), Vector3(0, 0, -1));
	Vector3 intersection;
	int width = _texture->getWidth();
	int height = _texture->getHeight();

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			//ray = camera.getRay(x, y);
			
			int index = bpp * (y + x * width);
			for (int k = 0; k < bpp; ++k)
			{
				//if (Collisions::RayAndSphere(ray, s, intersection))
					//_texture->getData()[index + k] = 200;
				//else
					_texture->getData()[index + k] = 0;
			}
		}
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
	camera.Position = position;
	camera.Rotation = rotation;
	camera.FOV = fov;
	camera.Width = width;
	camera.Height = height;
	camera.NearPlane = nearPlane;
	camera.FarPlane = farPlane;
	camera.ViewMatrix = viewMatrix;
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
