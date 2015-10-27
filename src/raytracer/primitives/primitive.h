#pragma once

#include "object.h"
#include "vector3.h"


namespace LumixRayTracer
{

class Primitive : public Object
{
public:

	Primitive()
		: Object()
	{
	}

	Primitive(const Vector3 position)
		: Object()
	{
		Position = position;
	}
};

} // ~ namespace LumixRayTracer
