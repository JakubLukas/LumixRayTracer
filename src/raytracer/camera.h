#pragma once

#include "vector3.h"
#include "quaternion.h"
#include "math_rt.h"

#include "ray.h"


namespace LumixRayTracer
{

class Camera
{
private:
	float _fovCache;
	Vector3 _up;
	Vector3 _right;
	Vector3 _forward;
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
		float u = (2.0f * x - 1.0f) * _fovCache;
		float v = (1.0f - 2.0f * y) * _fovCache;

		ray.Direction = _forward + _right * u + _up * v;
		ray.Position = Position + ray.Direction;
		ray.Direction.Normalize();
		ray.MaxDistance = FarPlane - NearPlane;
	}

	Vector3 GetDirection() const
	{
		return Rotation * Vector3(0.0f, 0.0f, -1.0f);
	}

	void OnChanged()
	{
		FOV = Math::RadFromDeg(FOV);
		_fovCache = Math::Tan(FOV * 0.5f) * NearPlane;

		_up = Rotation * Vector3(0.0f, 1.0f, 0.0f);
		_right = Rotation * Vector3(1.0f, 0.0f, 0.0f);
		_forward = Vector3::Cross(_up, _right) * NearPlane;
	}
};

} // ~ namespace LumixRayTracer
