#include "raytracer.h"

#include "vector3.h"
#include "ray.h"
#include "sphere.h"
#include "collisions.h"

#include "renderer/texture.h"


namespace LumixRayTracer
{

RayTracer::RayTracer()
{

}

RayTracer::~RayTracer()
{

}

void RayTracer::Update(const float &deltaTime, Lumix::Texture* texture)
{
	int bpp = texture->getBytesPerPixel();

	Sphere s(Vector3(0.0f, 0.0f, -2.0f), 2.0f);
	Ray ray;
	Vector3 intersection;
	for (unsigned int y = 0; y < texture->getHeight(); ++y)
	{
		for (unsigned int x = 0; x < texture->getWidth(); ++x)
		{
			ray = camera.getRay(x, y);
			
			int index = bpp * (y + x * texture->getWidth());
			for (int k = 0; k < bpp; ++k)
			{
				if (Collisions::RayAndSphere(ray, s, intersection))
					texture->getData()[index + k] = 200;
				else
					texture->getData()[index + k] = 0;
			}
		}
	}
}

void RayTracer::UpdateCamera(const Lumix::Vec3 &position,
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

} // ~namespace LumixRayTracer
