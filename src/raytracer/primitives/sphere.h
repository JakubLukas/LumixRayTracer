#pragma once

#include "primitive.h"
#include "vector3.h"


namespace LumixRayTracer
{

struct Sphere : public Primitive
{
	float Radius;

	Sphere()
		: Primitive(Vector3(0.0f, 0.0f, 0.0f)),
		Radius(1.0f)
	{
	}

	Sphere(const Vector3 &origin, const float &radius)
		: Primitive(origin),
		Radius(radius)
	{
	}
};

} // ~ namespace LumixRayTracer
