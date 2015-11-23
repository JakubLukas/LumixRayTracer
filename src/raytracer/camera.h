#pragma once

#include "vector3.h"
#include "vector4.h"
#include "quaternion.h"
#include "matrix44.h"
#include "math_rt.h"

#include "ray.h"


namespace LumixRayTracer
{

class Camera
{
private:
	float _fovTan;
	float _ratio;
public:
	Vector3 Position;
	Quaternion Rotation;
	float FOV;
	float Width;
	float Height;
	float NearPlane;
	float FarPlane;

	Camera()
		: Position(0.0f, 0.0f, 0.0f),
		Rotation(0.0f, 0.0f, 0.0f, 1.0f)
	{}

	void GetRay(const float x, const float y, Ray &ray) const
	{
		float px = (2.0f * x - 1.0f) * _fovTan * _ratio;
		float py = (1.0f - 2.0f * y) * _fovTan;

		ray.Direction = Rotation * Vector3(px, py, -1.0f);
		ray.Direction.normalize();

		ray.Position = Position;
	}

	Vector3 GetDirection() const
	{
		return Rotation * Vector3(0.0f, 0.0f, -1.0f);
	}

	void OnChanged()
	{
		FOV = Math::RadFromDeg(FOV);
		_fovTan = Math::Tan(FOV);

		_ratio = Width / Height;
	}
};

} // ~ namespace LumixRayTracer
