#pragma once

#include "vector3.h"


namespace LumixRayTracer
{
struct Vector3;

class Sampler
{
public:
	virtual Vector3 GetSample(float x, float y);
};

//-----------------------------------------------------------------------------

class ColorSampler : public Sampler
{
private:
	Vector3 _color;

public:
	ColorSampler();
	ColorSampler(const Vector3 color);

	virtual Vector3 GetSample(float x, float y) override;
};

} // ~ namespace LumixRayTracer
