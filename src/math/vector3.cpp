#include "vector3.h"


namespace LumixRayTracer
{

const float Vector3::EPSILON = 0.00001f;

Vector3::Vector3()
	: Vec3()
{
}

Vector3::Vector3(const int a, const int b, const int c)
	: Vec3((float)a, (float)b, (float)c)
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

} // ~ namespace LumixRayTracer
