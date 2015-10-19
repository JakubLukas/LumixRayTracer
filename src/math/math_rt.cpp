#include "math_rt.h"

#include <math.h>


namespace LumixRayTracer
{

namespace Math
{

float RadFromDeg(const float &angle)
{
	return angle * PI / 180.0f;
}

float DegFromRad(const float &angle)
{
	return angle / PI * 180.0f;
}

float Pow(const float &number, const float &exponent)
{
	return pow(number, exponent);
}

float Sqrt(const float &number)
{
	return sqrt(number);
}

} // ~ namespace Math

} // ~ namespace LumixRayTracer
