#include "matrix44.h"


namespace LumixRayTracer
{

Matrix44::Matrix44()
	: Matrix()
{
}

Matrix44::Matrix44(const float* m)
	: Matrix(m)
{
}

Matrix44::Matrix44(
	float r11, float r12, float r13, float r14,
	float r21, float r22, float r23, float r24,
	float r31, float r32, float r33, float r34,
	float r41, float r42, float r43, float r44
	)
	: Matrix(r11, r12, r13, r14,
					 r21, r22, r23, r24,
					 r31, r32, r33, r34,
					 r41, r42, r43, r44)
{
}

Matrix44::Matrix44(Lumix::Matrix m)
	: Matrix(m)
{
}

} // ~ namespace LumixRayTracer
