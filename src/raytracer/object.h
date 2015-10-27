#pragma once

#include "vector3.h"


namespace LumixRayTracer
{
class Material;

class Object
{
public:
	Material* ObjMaterial;
	Vector3 Position;

public:
	Object()
		: Position(0.0f, 0.0f, 0.0f)
	{}


};

} // ~ namespace LumixRayTracer
