#pragma once

#include "lumix.h"
#include "engine/core/quat.h"

namespace LumixRayTracer
{
struct Vector3;

struct Quaternion : public Lumix::Quat
{
	Quaternion();
	Quaternion(const Vector3& axis, float angle);
	Quaternion(float a, float b, float c, float d);
	Quaternion(Lumix::Quat v);
};

} // ~ namespace LumixRayTracer
