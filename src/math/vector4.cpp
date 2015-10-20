#include "vector4.h"

#include "vector3.h"

namespace LumixRayTracer
{

Vector4::Vector4()
	: Vec4()
{
}

Vector4::Vector4(float a, float b, float c, float d)
	: Vec4(a, b, c, d)
{
}

Vector4::Vector4(const Vector3& v, float d)
	: Vec4(v, d)
{
}

Vector4::Vector4(Lumix::Vec4 v)
	: Vec4(v)
{
}

Vector4& Vector4::operator *= (const float &f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

Vector4 operator *(const float &f, Vector4 v)
{
	return v *= f;
}

Vector4 operator *(Vector4 v, const float &f)
{
	return v *= f;
}

} // ~ namespace LumixRayTracer
