#include "raytracer.h"


namespace LumixRayTracer
{

struct RayTracer
{
	Camera camera;

	RayTracer()
	{

	}

	~RayTracer()
	{

	}

	void Update(const float &deltaTime)
	{

	}

	void UpdateCamera(const Lumix::Vec3 &position,
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

};

} // ~namespace LumixRayTracer
