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


} // ~ namespace LumixRayTracer
