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
	Sampler* _diffuseSampler;

public:
	PhongShader()
		: _diffuseSampler(nullptr)
	{
		_diffuseSampler = new ColorSampler(Vector3(1.0f, 1.0f, 1.0f));
	}
	~PhongShader()
	{
		delete _diffuseSampler;
	}

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Vector3 &camera, const Vector3 &light) override
	{
		Vector3 l = (light - point).normalized();
		float lDotN = Vector3::Dot(l, normal);
		return _diffuseSampler->GetSample(0, 0) * lDotN;
	}

};

} // ~ namespace LumixRayTracer
