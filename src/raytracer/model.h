#pragma once

#include "vector3.h"


namespace LumixRayTracer
{
class Material;

class Model
{
public:
	Material* ObjMaterial;
	Vector3 Position;

public:
	Model()
		: Position(0.0f, 0.0f, 0.0f)
	{}


};

} // ~ namespace LumixRayTracer
