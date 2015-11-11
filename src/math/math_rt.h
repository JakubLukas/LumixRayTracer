#pragma once

namespace LumixRayTracer
{

namespace Math
{
const float PI = 3.1415926535897932384626433832795f;

float RadFromDeg(const float degrees);
float DegFromRad(const float radians);

float Pow(const float number, const float exponent);
float Sqrt(const float number);

float Min(const float a, const float b);
float Max(const float a, const float b);
float Min(const float a, const float b, const float c);
float Max(const float a, const float b, const float c);
float Abs(const float number);
float Ceil(const float number);
float Floor(const float number);

float Mod(const float numer, const float denom);

float Tan(const float angle);

} // ~ namespace Math

} // ~ namespace LumixRayTracer
