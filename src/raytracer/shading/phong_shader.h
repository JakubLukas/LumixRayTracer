#pragma once

#include "shader.h"
#include "texturing/sampler.h"
#include "texturing/color_sampler.h"
#include "vector3.h"

namespace LumixRayTracer
{

class PhongShader : public Shader
{
private:
	Sampler _diffuseSampler;

public:
	PhongShader()
		: _diffuseSampler(ColorSampler(Vector3(1.0f, 1.0f, 1.0f)))
	{ }

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Vector3 &camera, const Vector3 &light) override
	{

	}

};

} // ~ namespace LumixRayTracer
