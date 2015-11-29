#include "vector3.h"

#include "engine/core/vec.h"


namespace LumixRayTracer
{

const float Vector3::EPSILON = 0.00001f;

Vector3::Vector3()
{
}

Vector3::Vector3(const int a, const int b, const int c)
	: x((float)a), y((float)b), z((float)c)
{
}

Vector3::Vector3(const float a, const float b, const float c)
	: x(a), y(b), z(c)
{
}

Vector3::Vector3(const Vector3& v)
	: x(v.x), y(v.y), z(v.z)
{
}

Vector3::Vector3(const Lumix::Vec3& v)
	: x(v.x), y(v.y), z(v.z)
{
}

} // ~ namespace LumixRayTracer
