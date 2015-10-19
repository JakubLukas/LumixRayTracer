#pragma once

#include "lumix.h"
#include "engine/core/matrix.h"

namespace LumixRayTracer
{

struct Matrix44 : public Lumix::Matrix
{
	Matrix44();
	Matrix44(const float* m);
	Matrix44(
		float r11, float r12, float r13, float r14,
		float r21, float r22, float r23, float r24,
		float r31, float r32, float r33, float r34,
		float r41, float r42, float r43, float r44
		);
	Matrix44(Lumix::Matrix m);
};

} // ~ namespace LumixRayTracer
