#pragma once

#include "object.h"
#include "vector3.h"


namespace LumixRayTracer
{

class Primitive : public Object
{
public:

	Primitive()
		: _position(0.0f, 0.0f, 0.0f)
	{
	}

	Primitive(const Vector3 position)
		: _position(position)
	{
	}
};

} // ~ namespace LumixRayTracer
