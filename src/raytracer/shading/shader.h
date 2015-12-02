#pragma once

#include "vector3.h"
#include "texturing/sampler.h"
#include "lightning/light.h"
#include "camera.h"


namespace LumixRayTracer
{
struct Vector3;
class Camera;
class Light;

//-----------------------------------------------------------------------------

class Shader
{
public:

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light)
	{
		return Vector3();
	}
};

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

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

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light) override
	{
		ASSERT(AmbientSampler != nullptr);
		ASSERT(DiffuseSampler != nullptr);
		ASSERT(SpecularSampler != nullptr);

		Vector3 lightDir = light.GetDirection(point);

		float lDotN = Vector3::Dot(-lightDir, normal);

		float spec = 0.0f;
		if (lDotN > 0.0f)
		{
			Vector3 r = 2.0f * lDotN * normal + lightDir;
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
