#pragma once

#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "matrix44.h"
#include "math_rt.h"

#include "ray.h"


namespace LumixRayTracer
{

struct Camera
{
	Vector3 Position;
	Quaternion Rotation;
	Matrix44 ViewMatrix;
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

		Matrix44 projection_matrix;
		projection_matrix.setPerspective(
			Math::RadFromDeg(FOV), ratio, NearPlane, FarPlane);
		ViewMatrix.inverse();
		Matrix44 inverted = (projection_matrix * ViewMatrix);
		inverted.inverse();
		Vector4 p0 = inverted * Vector4(nx, ny, -1, 1);
		Vector4 p1 = inverted * Vector4(nx, ny, 1, 1);
		p0.x /= p0.w;
		p0.y /= p0.w;
		p0.z /= p0.w;
		p1.x /= p1.w;
		p1.y /= p1.w;
		p1.z /= p1.w;

		Vector3 dir;
		dir.x = p1.x - p0.x;
		dir.y = p1.y - p0.y;
		dir.z = p1.z - p0.z;
		dir.normalize();

		return Ray(Position, dir);
	}
};

} // ~ namespace LumixRayTracer
