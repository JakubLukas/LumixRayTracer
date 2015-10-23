#include "vector3.h"


namespace LumixRayTracer
{

Vector3::Vector3()
	: Vec3()
{
}

Vector3::Vector3(const float a, const float b, const float c)
	: Vec3(a, b, c)
{
}

Vector3::Vector3(const Lumix::Vec3 v)
	: Vec3(v)
{
}

Vector3& Vector3::operator *= (const float f)
{
	x *= f;
	y *= f;
	z *= f;

	return *this;
}

Vector3 operator *(const float f, Vector3 v)
{
	return v *= f;
}

Vector3 operator *(Vector3 v, const float f)
{
	return v *= f;
}

float Vector3::Dot(const Vector3 v1, const Vector3 v2)
{
	return Lumix::dotProduct(v1, v2);
}

Vector3 Vector3::Cross(const Vector3 v1, const Vector3 v2)
{
	return Lumix::crossProduct(v1, v2);
}

} // ~ namespace LumixRayTracer
