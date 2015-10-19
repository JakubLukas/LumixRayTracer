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

static float Dot(Vector3 v1, Vector3 v2)
{
	return Lumix::dotProduct(v1, v2);
}

static Vector3 Cross(Vector3 v1, Vector3 v2)
{
	return Lumix::crossProduct(v1, v2);
}

} // ~ namespace LumixRayTracer
