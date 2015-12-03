#include "sampler.h"


namespace LumixRayTracer
{


Vector3 Sampler::GetSample(float x, float y)
{
	return Vector3();
};

//-----------------------------------------------------------------------------

ColorSampler::ColorSampler()
	: _color(1.0f, 0.0f, 0.0f)
{
}

ColorSampler::ColorSampler(const Vector3 color)
	: _color(color)
{
}

Vector3 ColorSampler::GetSample(float x, float y)
{
	return _color;
}

} // ~ namespace LumixRayTracer
