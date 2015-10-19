#include "vector3.h"


namespace LumixRayTracer
{

Vector3::Vector3()
	: Vec3()
{
}

Vector3::Vector3(float a, float b, float c)
	: Vec3(a, b, c)
{
}

Vector3::Vector3(Lumix::Vec3 v)
	: Vec3(v)
{
}

Vector3 Vector3::operator *(float f)
{
	return Vector3(f * x, f * y, f * z);
}

Vector3 operator *(float f, const Vector3 &v)
{
	return Vector3(f * v.x, f * v.y, f * v.z);
}

float Vector3::Dot(Vector3 v1, Vector3 v2)
{
	return Lumix::dotProduct(v1, v2);
}

Vector3 Vector3::Cross(Vector3 v1, Vector3 v2)
{
	return Lumix::crossProduct(v1, v2);
}

} // ~ namespace LumixRayTracer
