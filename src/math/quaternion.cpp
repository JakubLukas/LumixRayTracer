#include "quaternion.h"


namespace LumixRayTracer
{

Quaternion::Quaternion()
	: Quat()
{
}

Quaternion::Quaternion(const Vector3& axis, const float angle)
	: Quat(axis, angle)
{
}

Quaternion::Quaternion(const float a, const float b, const float c, const float d)
	: Quat(a, b, c, d)
{
}

Quaternion::Quaternion(Lumix::Quat v)
	: Quat(v)
{
}

} // ~ namespace LumixRayTracer
