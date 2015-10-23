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
private:
	float _fovTan;
	float _ratio;
public:
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

	void getRay(float x, float y, Ray &ray)
	{
		float px = (2.0f * x - 1.0f) * _fovTan * _ratio;
		float py = (1.0f - 2.0f * y) * _fovTan;

		ray.Direction.x = px;// - Position.x;
		ray.Direction.y = py;// - Position.y;
		ray.Direction.z = -1.0f;// - Position.z;
		ray.Direction.normalize();

		ray.Position.x = 0.0f;// Position.x;
		ray.Position.y = 0.0f;// Position.y;
		ray.Position.z = 0.0f;// Position.z;
	}

	void OnChanged()
	{
		FOV = Math::RadFromDeg(FOV);
		_fovTan = Math::Tan(FOV);

		_ratio = Width / Height;
	}
};

} // ~ namespace LumixRayTracer
