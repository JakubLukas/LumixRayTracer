#pragma once

#include "model.h"
#include "vector3.h"


namespace LumixRayTracer
{

class Primitive : public Model
{
public:

	Primitive()
		: Model()
	{
	}

	Primitive(const Vector3 position)
		: Model()
	{
		Position = position;
	}
};

} // ~ namespace LumixRayTracer
