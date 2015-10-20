#pragma once

#include "lumix.h"
#include "engine/core/vec4.h"

namespace LumixRayTracer
{
struct Vector3;

struct Vector4 : public Lumix::Vec4
{
	Vector4();
	Vector4(float a, float b, float c, float d);
	Vector4(const Vector3& v, float d);
	Vector4(Lumix::Vec4 v);

	Vector4& operator *=(const float &f);

};

Vector4 operator *(const float &f, Vector4 v);
Vector4 operator *(Vector4 v, const float &f);

} // ~ namespace LumixRayTracer
