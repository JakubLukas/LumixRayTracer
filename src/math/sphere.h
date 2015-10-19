#pragma once

#include "vector3.h"


namespace LumixRayTracer
{

struct Sphere
{
	Vector3 Position;
	float Radius;

	Sphere()
		: Position(0.0f, 0.0f, 0.0f),
		Radius(1.0f)
	{
	}

	Sphere(const Vector3 &origin, const float &radius)
		: Position(origin),
		Radius(radius)
	{
	}
};

} // ~ namespace LumixRayTracer
