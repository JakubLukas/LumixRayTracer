#include "math_rt.h"

#include <math.h>


namespace LumixRayTracer
{

namespace Math
{

float RadFromDeg(const float angle)
{
	return angle * PI / 180.0f;
}

float DegFromRad(const float angle)
{
	return angle / PI * 180.0f;
}

float Pow(const float number, const float exponent)
{
	return pow(number, exponent);
}

float Sqrt(const float number)
{
	return sqrt(number);
}

float Min(float a, float b)
{
	return a < b ? a : b;
}

float Max(float a, float b)
{
	return a < b ? b : a;
}

float Abs(const float number)
{
	return abs(number);
}

float Tan(const float angle)
{
	return tan(angle);
}

} // ~ namespace Math

} // ~ namespace LumixRayTracer
