#pragma once

namespace LumixRayTracer
{

namespace Math
{
const float PI = 3.1415926535897932384626433832795f;

//-------------------------------------------------------------------

inline float RadFromDeg(const float angle)
{
	return angle * PI / 180.0f;
}

inline float DegFromRad(const float angle)
{
	return angle / PI * 180.0f;
}

//-------------------------------------------------------------------

inline float Pow(const float number, const float exponent)
{
	return powf(number, exponent);
}

inline float Sqrt(const float number)
{
	return sqrtf(number);
}

//-------------------------------------------------------------------

inline float Min(const float a, const float b)
{
	return a < b ? a : b;
}

inline float Max(const float a, const float b)
{
	return a < b ? b : a;
}

inline float Min(const float a, const float b, const float c)
{
	return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

inline float Max(const float a, const float b, const float c)
{
	return a < b ? (b < c ? c : b) : (a < c ? c : a);
}

inline float Abs(const float number)
{
	return fabsf(number);
}

inline float Ceil(const float number)
{
	return ceilf(number);
}

inline float Floor(const float number)
{
	return floorf(number);
}

//-------------------------------------------------------------------

inline float Mod(const float numer, const float denom)
{
	return fmod(numer, denom);
}

inline float Tan(const float angle)
{
	return tanf(angle);
}

} // ~ namespace Math

} // ~ namespace LumixRayTracer
