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

} // ~ namespace LumixRayTracer
