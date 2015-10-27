#pragma once

#include "lumix.h"
#include "vector3.h"
#include "model.h"


namespace LumixRayTracer
{

struct RayHit
{
	Vector3 Position;
	Vector3 Normal;
	Model* HitObject;
};

} // ~ namespace LumixRayTracer
