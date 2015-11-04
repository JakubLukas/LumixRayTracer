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

float Min(float a, float b);
float Max(float a, float b);
float Abs(const float number);

float Tan(const float angle);

} // ~ namespace Math

} // ~ namespace LumixRayTracer
