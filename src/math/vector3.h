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
	Vector3(const int a, const int b, const int c);
	Vector3(const float a, const float b, const float c);
	Vector3(const Lumix::Vec3 v);

	inline Vector3& operator *=(const float f);

	inline static float Dot(const Vector3 v1, const Vector3 v2);
	inline static Vector3 Cross(const Vector3 v1, const Vector3 v2);
};

//-------------------------------------------------------------------

inline Vector3& Vector3::operator *= (const float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

inline Vector3 operator *(const float f, Vector3 v)
{
	return v *= f;
}

inline Vector3 operator *(Vector3 v, const float f)
{
	return v *= f;
}

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

inline float Vector3::Dot(const Vector3 v1, const Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline Vector3 Vector3::Cross(const Vector3 v1, const Vector3 v2)
{
	return Vector3(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
		);
}

namespace Math
{
inline Vector3 Min(const Vector3& v, const float a)
{
	return Vector3(Math::Min(v.x, a), Math::Min(v.y, a), Math::Min(v.z, a));
}

inline Vector3 Max(const Vector3& v, const float a)
{
	return Vector3(Math::Max(v.x, a), Math::Max(v.y, a), Math::Max(v.z, a));
}

inline Vector3 Clamp(const Vector3& v, const float min, const float max)
{
	return Vector3(Math::Clamp(v.x, min, max),
				   Math::Clamp(v.y, min, max),
				   Math::Clamp(v.z, min, max));
}

} // namespace Math

} // namespace LumixRayTracer
