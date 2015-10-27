#pragma once

#include "sampler.h"
#include "vector3.h"

namespace LumixRayTracer
{

class ColorSampler : public Sampler
{
private:
	Vector3 _color;

public:
	ColorSampler()
		: _color(1.0f, 0.0f, 0.0f)
	{ }

	ColorSampler(const Vector3 color)
		: _color(color)
	{ }

	virtual Vector3 GetSample(float x, float y) override
	{
		return _color;
	}

};

} // ~ namespace LumixRayTracer
