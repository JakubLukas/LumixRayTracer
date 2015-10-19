#include "math_rt.h"


namespace LumixRayTracer
{

namespace Math
{

float RadFromDeg(float angle)
{
	return angle * PI / 180.0f;
}

float DegFromRad(float angle)
{
	return angle / PI * 180.0f;
}

} // ~ namespace Math

} // ~ namespace LumixRayTracer
