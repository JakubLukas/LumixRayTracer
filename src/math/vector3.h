#pragma once

#include "lumix.h"
#include "engine/core/vec3.h"

namespace LumixRayTracer
{

struct Vector3 : public Lumix::Vec3
{
	Vector3();
	Vector3(const float a, const float b, const float c);
	Vector3(const Lumix::Vec3 v);

	Vector3& operator *=(const float f);

	static float Dot(const Vector3 v1, const Vector3 v2);
	static Vector3 Cross(const Vector3 v1, const Vector3 v2);
};

Vector3 operator *(const float f, Vector3 v);
Vector3 operator *(Vector3 v, const float f);

} // ~ namespace LumixRayTracer
