#pragma once

#include "primitive.h"
#include "vector3.h"


namespace LumixRayTracer
{

struct Box : public Primitive
{
	Vector3 Size;

	Box()
		: Primitive(Vector3(0.0f, 0.0f, 0.0f)),
		Size(1.0f, 1.0f, 1.0f)
	{
	}

	Box(const Vector3 &origin, const Vector3 &size)
		: Primitive(origin),
		Size(size)
	{
	}
};

} // ~ namespace LumixRayTracer
