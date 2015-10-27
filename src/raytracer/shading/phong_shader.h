#pragma once

#include "shader.h"
#include "texturing/sampler.h"
#include "texturing/color_sampler.h"
#include "vector3.h"

namespace LumixRayTracer
{

class PhongShader : public Shader
{
public:
	Sampler* DiffuseSampler;

public:
	PhongShader(Sampler *diffuse)
		: DiffuseSampler(diffuse)
	{
	}

	~PhongShader()
	{
		delete DiffuseSampler;
	}

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Vector3 &camera, const Vector3 &light) override
	{
		ASSERT(DiffuseSampler != nullptr);

		Vector3 l = (light - point).normalized();
		float lDotN = Vector3::Dot(l, normal);
		return DiffuseSampler->GetSample(0, 0) * lDotN;
	}

};

} // ~ namespace LumixRayTracer
