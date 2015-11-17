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
	Sampler* SpecularSampler;
	float Shininess;

public:
	PhongShader(Sampler *ambient, Sampler *diffuse, Sampler *specular, const float shininess)
		: AmbientSampler(ambient),
		DiffuseSampler(diffuse),
		SpecularSampler(specular),
		Shininess(shininess)
	{
	}

	~PhongShader()
	{
	}

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const DirectionalLight &light) override
	{
		ASSERT(AmbientSampler != nullptr);
		ASSERT(DiffuseSampler != nullptr);
		ASSERT(SpecularSampler != nullptr);

		float lDotN = Vector3::Dot(-light.Direction, normal);

		float spec = 0.0f;
		if (lDotN > 0.0f)
		{
			Vector3 r = 2.0f * lDotN * normal + light.Direction;
			float rDotV = Vector3::Dot(r, camera.Position - point);
			spec = Math::Pow(rDotV, Shininess);
		}

		Vector3 color = AmbientSampler->GetSample(0, 0)
			+ DiffuseSampler->GetSample(0, 0) * Math::Max(lDotN, 0.0f)
			+ SpecularSampler->GetSample(0, 0) * Math::Clamp(spec, 0.0f, 1.0f);

		return Math::Clamp(color, 0.0f, 1.0f);
	}

};

} // ~ namespace LumixRayTracer
