#pragma once

#include "lumix.h"
#include "vector3.h"
#include <float.h>


namespace LumixRayTracer
{

struct Ray
{
	Vector3 Position;
	Vector3 Direction;
	float MaxDistance;

	Ray()
		: Position(0.0f, 0.0f, 0.0f),
		Direction(0.0f, 0.0f, 1.0f),
		MaxDistance(FLT_MAX)
	{}

	Ray(const Vector3 &origin, const Vector3 &direction)
		: Position(origin),
		Direction(direction),
		MaxDistance(FLT_MAX)
	{}
};

} // ~ namespace LumixRayTracer
