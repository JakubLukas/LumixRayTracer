#pragma once

#include "lumix.h"
#include "engine/core/vec3.h"

namespace LumixRayTracer
{

struct Vector3 : public Lumix::Vec3
{
	Vector3();
	Vector3(float a, float b, float c);
	Vector3(Lumix::Vec3 v);

	Vector3 operator *(float f);

	static float Dot(Vector3 v1, Vector3 v2);
	static Vector3 Cross(Vector3 v1, Vector3 v2);
};

Vector3 operator *(float f, const Vector3 &v);

} // ~ namespace LumixRayTracer
