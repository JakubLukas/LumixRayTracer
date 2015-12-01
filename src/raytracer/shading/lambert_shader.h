#pragma once

#include "shader.h"
#include "texturing/sampler.h"
#include "vector3.h"
#include "lightning/light.h"

namespace LumixRayTracer
{

class LambertShader : public Shader
{
public:
	Sampler* AmbientSampler;
	Sampler* DiffuseSampler;

public:
	LambertShader(Sampler *ambient, Sampler *diffuse)
		: AmbientSampler(ambient),
		DiffuseSampler(diffuse)
	{
	}

	~LambertShader()
	{
	}

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light) override
	{
		ASSERT(AmbientSampler != nullptr);
		ASSERT(DiffuseSampler != nullptr);

		Vector3 lightDir = light.GetDirection(point);

		float lDotN = Vector3::Dot(-lightDir, normal);
		return AmbientSampler->GetSample(0, 0)
			+ DiffuseSampler->GetSample(0, 0) * Math::Max(lDotN, 0.0f);
	}

};

} // ~ namespace LumixRayTracer
