#pragma once

#include "math_rt.h"

namespace Lumix
{
	struct Vec3;
}


namespace LumixRayTracer
{

struct Vector3
{
	static const float EPSILON;

	float x;
	float y;
	float z;

	Vector3();
	Vector3(const int a, const int b, const int c);
	Vector3(const float a, const float b, const float c);
	Vector3(const Vector3& v);
	Vector3(const Lumix::Vec3& v);

	inline Vector3 operator - () const;

	inline Vector3 operator + (const Vector3& v) const;
	inline void operator += (const Vector3& v);

	inline Vector3 operator - (const Vector3& v) const;
	inline void operator -= (const Vector3& v);

	inline Vector3 operator * (const float s) const;
	inline void operator *=(const float s);

	inline Vector3 operator / (const float s) const;
	inline void operator /= (const float s);

	inline void Normalize();
	inline Vector3 Normalized() const;

	inline float Length() const;
	inline float LengthSquared() const;

	inline void Set(const float x, const float y, const float z);

	inline static float Dot(const Vector3 v1, const Vector3 v2);
	inline static Vector3 Cross(const Vector3 v1, const Vector3 v2);
};

//-------------------------------------------------------------------

inline Vector3 Vector3::operator - () const
{
	return Vector3(-x, -y, -z);
}

//-------------------------------------------------------------------

inline Vector3 Vector3::operator + (const Vector3& v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

inline void Vector3::operator += (const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

//-------------------------------------------------------------------

inline Vector3 Vector3::operator - (const Vector3& v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

void Vector3::operator -= (const Vector3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

//-------------------------------------------------------------------

inline Vector3 Vector3::operator * (const float s) const
{
	return Vector3(x * s, y * s, z * s);
}

inline Vector3 operator * (const float s, const Vector3& v)
{
	return v * s;
}

inline void Vector3::operator *= (const float s)
{
	x *= s;
	y *= s;
	z *= s;
}

//-------------------------------------------------------------------

inline Vector3 Vector3::operator / (const float s) const
{
	float tmp = 1.0f / s;
	return Vector3(x * tmp, y * tmp, z * tmp);
}

inline Vector3 operator / (const float s, const Vector3& v)
{
	return v / s;
}

inline void Vector3::operator /= (const float s)
{
	float tmp = 1.0f / s;
	x *= tmp;
	y *= tmp;
	z *= tmp;
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

inline void Vector3::Normalize()
{
	float inv_len = 1.0f / sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	*this *= inv_len;
}

inline Vector3 Vector3::Normalized() const
{
	Vector3 v(*this);
	float inv_len = 1.0f / sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	v *= inv_len;
	return v;
}

inline float Vector3::Length() const
{
	return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

inline float Vector3::LengthSquared() const
{
	return (this->x * this->x + this->y * this->y + this->z * this->z);
}

inline void Vector3::Set(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
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

//-------------------------------------------------------------------
//-------------------------------------------------------------------

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
