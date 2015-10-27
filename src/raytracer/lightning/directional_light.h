#pragma once

#include "light.h"
#include "vector3.h"

namespace LumixRayTracer
{

struct DirectionalLight : public Light
{
	Vector3 Direction;

	DirectionalLight()
		: Direction(0.0f, -1.0f, 0.0f)
	{ }

	DirectionalLight(const Vector3 direction)
		: Direction(direction)
	{ }

};

} // ~ namespace LumixRayTracer
