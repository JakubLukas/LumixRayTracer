#pragma once

#include "light.h"
#include "vector3.h"

namespace LumixRayTracer
{

class DirectionalLight : public Light
{
public:
	Vector3 Direction;

public:
	DirectionalLight()
		: Direction(0.0f, -1.0f, 0.0f)
	{ }

	DirectionalLight(const Vector3 &direction)
		: Direction(direction.Normalized())
	{ }

};

} // ~ namespace LumixRayTracer
