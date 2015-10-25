#pragma once

#include "lumix.h"
#include "vector3.h"


namespace LumixRayTracer
{

struct Ray
{
	Vector3 Position;
	Vector3 Direction;

	Ray()
		: Position(0.0f, 0.0f, 0.0f),
		Direction(0.0f, 0.0f, 1.0f)
	{}

	Ray(const Vector3 &origin, const Vector3 &direction)
		: Position(origin),
		Direction(direction)
	{}
};

} // ~ namespace LumixRayTracer
