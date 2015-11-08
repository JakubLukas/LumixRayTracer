#pragma once

#include "lumix.h"
#include "engine/core/vec3.h"
#include "math_rt.h"

namespace LumixRayTracer
{

struct Vector3 : public Lumix::Vec3
{
	static const float EPSILON;

	Vector3();
	Vector3(const float a, const float b, const float c);
	Vector3(const Lumix::Vec3 v);

	Vector3& operator *=(const float f);

	static float Dot(const Vector3 v1, const Vector3 v2);
	static Vector3 Cross(const Vector3 v1, const Vector3 v2);
};

Vector3 operator *(const float f, Vector3 v);
Vector3 operator *(Vector3 v, const float f);
inline bool operator==(const Vector3& lhs, const Vector3& rhs)
{
	if (Math::Abs(lhs.x - rhs.x) < Vector3::EPSILON)
		return false;
	if (Math::Abs(lhs.y - rhs.y) < Vector3::EPSILON)
		return false;
	if (Math::Abs(lhs.z - rhs.z) < Vector3::EPSILON)
		return false;

	return true;
}

inline bool operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

} // ~ namespace LumixRayTracer
