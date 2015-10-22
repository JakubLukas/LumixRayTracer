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
	Matrix44 _projectionMatrix;

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
		//float nx = 2.0f * (x / Width) - 1.0f;
		//float ny = 2.0f * ((Height - y) / Height) - 1.0f;

		//Matrix44 tmp = ViewMatrix;
		//tmp.inverse();
		Matrix44 inverted = (_projectionMatrix /** tmp*/);
		inverted.inverse();
		Vector4 p0 = inverted * Vector4(x, y, -1, 1);
		Vector4 p1 = inverted * Vector4(x, y, 1, 1);
		p0.x /= p0.w;
		p0.y /= p0.w;
		p0.z /= p0.w;
		p1.x /= p1.w;
		p1.y /= p1.w;
		p1.z /= p1.w;

		ray.Direction.x = p1.x - p0.x;
		ray.Direction.y = p1.y - p0.y;
		ray.Direction.z = p1.z - p0.z;
		ray.Direction.normalize();

		//ray.Position = Position;
		//ray.Direction = Vector3(0.0f, 0.0f, -1.0f);
	}

	void OnChanged()
	{
		FOV = Math::RadFromDeg(FOV);

		float ratio = Width / Height;
		_projectionMatrix.setPerspective(FOV, ratio, NearPlane, FarPlane);
	}
};

} // ~ namespace LumixRayTracer
