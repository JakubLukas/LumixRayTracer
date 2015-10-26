#pragma once

#include "lumix.h"
#include "vector3.h"
#include "object.h"


namespace LumixRayTracer
{

struct RayHit
{
	Vector3 Position;
	Vector3 Normal;
	Object* HitObject;
};

} // ~ namespace LumixRayTracer
