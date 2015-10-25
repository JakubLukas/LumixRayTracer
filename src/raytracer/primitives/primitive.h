#pragma once

#include "vector3.h"


namespace LumixRayTracer
{

class Primitive
{
public:
	Vector3 Position;

	Primitive()
		: Position(0.0f, 0.0f, 0.0f)
	{
	}

	Primitive(const Vector3 position)
		: Position(position)
	{
	}
};

} // ~ namespace LumixRayTracer
