#pragma once

#include "math_rt.h"
#include "vector3.h"
#include "matrix44.h"


namespace Lumix
{
	struct Quat;
}

namespace LumixRayTracer
{
struct Vector3;

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(const Vector3& axis, const float angle);
	Quaternion(const float a, const float b, const float c, const float d);
	Quaternion(const Quaternion& q);
	Quaternion(const Lumix::Quat& q);

	inline void FromEuler(const Vector3& euler);
	inline Vector3 ToEuler() const;

	inline void GetAxisAngle(Vector3& axis, float& angle) const;

	inline void Conjugate();
	inline void Conjugated(Quaternion& q);

	inline void Normalize();
	inline void ToMatrix(Matrix44& mtx) const;

	inline void Set(const float x, const float y, const float z, const float w);

	inline Vector3 operator * (const Vector3& v) const;
	inline Quaternion operator * (const Quaternion& q) const;
	inline Quaternion operator - () const;

	static inline void Lerp(const Quaternion& q1, const Quaternion& q2, Quaternion& out, const float t);
};

//-------------------------------------------------------------------

inline void Quaternion::FromEuler(const Vector3& euler)
{
	float ex = euler.x * 0.5f;
	float ey = euler.y * 0.5f;
	float ez = euler.z * 0.5f;
	float sinX = Math::Sin(ex);
	float cosX = Math::Cos(ex);
	float sinY = Math::Sin(ey);
	float cosY = Math::Cos(ey);
	float sinZ = Math::Sin(ez);
	float cosZ = Math::Cos(ez);

	w = cosY * cosX * cosZ + sinY * sinX * sinZ;
	x = cosY * sinX * cosZ + sinY * cosX * sinZ;
	y = sinY * cosX * cosZ - cosY * sinX * sinZ;
	z = cosY * cosX * sinZ - sinY * sinX * cosZ;
}

// Thanks: urho3d
inline Vector3 Quaternion::ToEuler() const
{
	float check = 2.0f * (-y * z + w * x);

	if (check < -0.995f)
	{
		return Vector3(-Math::PI * 0.5f, 0.0f, -Math::Atan2(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)));
	}
	else if (check > 0.995f)
	{
		return Vector3(Math::PI * 0.5f, 0.0f, Math::Atan2(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)));
	}
	else
	{
		return Vector3(Math::Asin(check),
					Math::Atan2(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y * y)),
					Math::Atan2(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z)));
	}
}

//-------------------------------------------------------------------

inline void Quaternion::GetAxisAngle(Vector3& axis, float& angle) const
{
	static const float EPSILON = 0.00001f;

	if (Math::Abs(1 - w*w) < EPSILON)
	{
		angle = 0.0f;
		axis.Set(0.0f, 1.0f, 0.0f);
	}
	else
	{
		angle = 2.0f * Math::Acos(w);
		float tmp = 1.0f / Math::Sqrt(1 - w*w);
		axis.Set(x * tmp, y * tmp, z * tmp);
	}
}

//-------------------------------------------------------------------

inline void Quaternion::Conjugate()
{
	w = -w;
}


inline void Quaternion::Conjugated(Quaternion& q)
{
	q.x = x;
	q.y = y;
	q.z = z;
	q.w = -w;
}

//-------------------------------------------------------------------

inline void Quaternion::Normalize()
{
	float len = 1.0f / Math::Sqrt(x*x + y*y + z*z + w*w);
	x *= len;
	y *= len;
	z *= len;
	w *= len;
}

void Quaternion::ToMatrix(Matrix44& mtx) const
{
	float fx = x + x;
	float fy = y + y;
	float fz = z + z;
	float fwx = fx*w;
	float fwy = fy*w;
	float fwz = fz*w;
	float fxx = fx*x;
	float fxy = fy*x;
	float fxz = fz*x;
	float fyy = fy*y;
	float fyz = fz*y;
	float fzz = fz*z;

	mtx.m11 = 1.0f - (fyy + fzz);
	mtx.m21 = fxy - fwz;
	mtx.m31 = fxz + fwy;
	mtx.m12 = fxy + fwz;
	mtx.m22 = 1.0f - (fxx + fzz);
	mtx.m32 = fyz - fwx;
	mtx.m13 = fxz - fwy;
	mtx.m23 = fyz + fwx;
	mtx.m33 = 1.0f - (fxx + fyy);

	mtx.m41 = mtx.m42 = mtx.m43 = mtx.m14 = mtx.m24 = mtx.m34 = 0.0f;
	mtx.m44 = 1.0f;
}

//-------------------------------------------------------------------

inline void Quaternion::Set(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

//-------------------------------------------------------------------

inline Vector3 Quaternion::operator * (const Vector3& v) const
{
	// nVidia SDK implementation
	/*Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = Vector3::Cross(qvec, v);
	uuv = Vector3::Cross(qvec, uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;*/

	Vector3 u(x, y, z);

	return 2.0f * Vector3::Dot(u, v) * u
		+ (w*w - Vector3::Dot(u, u)) * v
		+ 2.0f * w * Vector3::Cross(u, v);
}

inline Quaternion Quaternion::operator * (const Quaternion& q) const
{
	Quaternion result;

	result.w = (q.w * w) - (q.x * x) - (q.y * y) - (q.z * z);
	result.x = (q.w * x) + (q.x * w) + (q.y * z) - (q.z * y);
	result.y = (q.w * y) + (q.y * w) + (q.z * x) - (q.x * z);
	result.z = (q.w * z) + (q.z * w) + (q.x * y) - (q.y * x);

	return result;
}

inline Quaternion Quaternion::operator - () const
{
	return Quaternion(x, y, z, -w);
}

} // ~ namespace LumixRayTracer
