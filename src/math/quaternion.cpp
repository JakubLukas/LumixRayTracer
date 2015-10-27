#include "quaternion.h"

#include "vector3.h"

namespace LumixRayTracer
{

Quaternion::Quaternion()
	: Quat()
{
}

Quaternion::Quaternion(const Vector3& axis, float angle)
	: Quat(axis, angle)
{
}

Quaternion::Quaternion(float a, float b, float c, float d)
	: Quat(a, b, c, d)
{
}

Quaternion::Quaternion(Lumix::Quat v)
	: Quat(v)
{
}

Vector3 Quaternion::operator *(const Vector3& v) const
{
	// nVidia SDK implementation

	Vector3 uv, uuv;
	Vector3 qvec(x, y, z);
	uv = crossProduct(qvec, v);
	uuv = crossProduct(qvec, uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return v + uv + uuv;
}


} // ~ namespace LumixRayTracer
