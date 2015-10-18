#pragma once

#include "lumix.h"
#include "engine/core/vec3.h"


namespace LumixRayTracer
{

struct Ray
{
	Lumix::Vec3 Position;
	Lumix::Vec3 Direction;

	Ray()
		: Position(0.0f, 0.0f, 0.0f),
		Direction(0.0f, 0.0f, 1.0f)
	{}

	Ray(const Lumix::Vec3 &origin, const Lumix::Vec3 &direction)
		: Position(origin),
		Direction(direction)
	{}
};

} // ~ namespace LumixRayTracer
