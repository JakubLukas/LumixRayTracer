#pragma once

#include "lumix.h"
#include "engine/core/vec3.h"
#include "engine/core/quat.h"
#include "engine/core/matrix.h"
#include "engine/core/math_utils.h"

#include "ray.h"


namespace LumixRayTracer
{

struct Camera
{
	Lumix::Vec3 Position;
	Lumix::Quat Rotation;
	Lumix::Matrix ViewMatrix;
	float FOV;
	float Width;
	float Height;
	float NearPlane;
	float FarPlane;

	Camera()
		: Position(0.0f, 0.0f, 0.0f),
		Rotation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	Ray getRay(float x, float y)
	{
		float nx = 2 * (x / Width) - 1;
		float ny = 2 * ((Height - y) / Height) - 1;

		float ratio = Width / Height;

		Lumix::Matrix projection_matrix;
		projection_matrix.setPerspective(
			Lumix::Math::degreesToRadians(FOV), ratio, NearPlane, FarPlane);
		ViewMatrix.inverse();
		Lumix::Matrix inverted = (projection_matrix * ViewMatrix);
		inverted.inverse();
		Lumix::Vec4 p0 = inverted * Lumix::Vec4(nx, ny, -1, 1);
		Lumix::Vec4 p1 = inverted * Lumix::Vec4(nx, ny, 1, 1);
		p0.x /= p0.w;
		p0.y /= p0.w;
		p0.z /= p0.w;
		p1.x /= p1.w;
		p1.y /= p1.w;
		p1.z /= p1.w;

		Lumix::Vec3 dir;
		dir.x = p1.x - p0.x;
		dir.y = p1.y - p0.y;
		dir.z = p1.z - p0.z;
		dir.normalize();

		return Ray(Position, dir);
	}
};

} // ~ namespace LumixRayTracer
