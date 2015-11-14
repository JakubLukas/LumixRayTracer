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

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const DirectionalLight &light) override
	{
		ASSERT(DiffuseSampler != nullptr);

		Vector3 l = light.Direction;//(light.Direction - point).normalized();
		float lDotN = Vector3::Dot(l, normal);
		return DiffuseSampler->GetSample(0, 0) * Math::Max(lDotN, 0.0f);
	}

};

} // ~ namespace LumixRayTracer
