#include "raytracer.h"

#include "ray.h"


namespace LumixRayTracer
{

RayTracer::RayTracer()
{

}

RayTracer::~RayTracer()
{

}

void RayTracer::Update(const float &deltaTime)
{
	for (unsigned int y = 0; y < camera.Height; ++y)
	{
		for (unsigned int x = 0; x < camera.Height; ++x)
		{
			Ray ray = camera.getRay(x, y);
			//if ()
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
