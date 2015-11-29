#include "quaternion.h"

#include "engine/core/quat.h"


namespace LumixRayTracer
{

Quaternion::Quaternion()
	: x(0.0f), y(0.0f), z(0.0f), w(1.0f)
{
}

Quaternion::Quaternion(const Vector3& axis, const float angle)
{
	float half_angle = angle * 0.5f;
	float s = Math::Sin(half_angle);
	w = Math::Cos(half_angle);
	x = axis.x * s;
	y = axis.y * s;
	z = axis.z * s;
}

Quaternion::Quaternion(const float a, const float b, const float c, const float d)
	: x(a), y(b), z(c), w(d)
{
}

Quaternion::Quaternion(const Quaternion& q)
	: x(q.x), y(q.y), z(q.z), w(q.w)
{
}

Quaternion::Quaternion(const Lumix::Quat& q)
	: x(q.x), y(q.y), z(q.z), w(q.w)
{
}

//-------------------------------------------------------------------

static inline void Lerp(const Quaternion& q1, const Quaternion& q2, Quaternion& out, const float t)
{
	float inv = 1.0f - t;
	float ox = q1.x * inv + q2.x * t;
	float oy = q1.y * inv + q2.y * t;
	float oz = q1.z * inv + q2.z * t;
	float ow = q1.w * inv + q2.w * t;
	float len = 1.0f / Math::Sqrt(ox * ox + oy * oy + oz * oz + ow * ow);
	out.x = ox * len;
	out.y = oy * len;
	out.z = oz * len;
	out.w = ow * len;
}

} // ~ namespace LumixRayTracer
