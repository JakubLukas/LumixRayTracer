#pragma once

#include "shader.h"
#include "texturing/sampler.h"
#include "texturing/color_sampler.h"
#include "vector3.h"
#include "lightning/directional_light.h"

namespace LumixRayTracer
{

class PhongShader : public Shader
{
public:
	Sampler* AmbientSampler;
	Sampler* DiffuseSampler;

public:
	PhongShader(Sampler *ambient, Sampler *diffuse)
		: AmbientSampler(ambient),
		DiffuseSampler(diffuse)
	{
	}

	~PhongShader()
	{
	}

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const DirectionalLight &light) override
	{
		ASSERT(DiffuseSampler != nullptr);

		float lDotN = Vector3::Dot(light.Direction, normal);
		return AmbientSampler->GetSample(0, 0)
			+ DiffuseSampler->GetSample(0, 0) * Math::Max(lDotN, 0.0f);
	}

};

} // ~ namespace LumixRayTracer
