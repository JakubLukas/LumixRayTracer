#pragma once

#include "lumix.h"
#include "engine/core/quat.h"
#include "vector3.h"


namespace LumixRayTracer
{
struct Vector3;

struct Quaternion : public Lumix::Quat
{
	Quaternion();
	Quaternion(const Vector3& axis, float angle);
	Quaternion(float a, float b, float c, float d);
	Quaternion(Lumix::Quat v);

	inline Vector3 operator *(const Vector3& v) const;
};

//-------------------------------------------------------------------

inline Vector3 Quaternion::operator *(const Vector3& v) const
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

} // ~ namespace LumixRayTracer
