#include "shader.h"

#include "vector3.h"
#include "texturing/sampler.h"
#include "lightning/light.h"
#include "camera.h"


namespace LumixRayTracer
{

Vector3 Shader::GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light)
{
	return Vector3();
}

//-----------------------------------------------------------------------------

LambertShader::LambertShader(Sampler *ambient, Sampler *diffuse)
	: AmbientSampler(ambient),
	DiffuseSampler(diffuse)
{
}

LambertShader::~LambertShader()
{
}

Vector3 LambertShader::GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light)
{
	ASSERT(AmbientSampler != nullptr);
	ASSERT(DiffuseSampler != nullptr);

	Vector3 lightDir = light.GetDirection(point);

	float lDotN = Vector3::Dot(-lightDir, normal);
	Vector3 color = AmbientSampler->GetSample(0, 0)
		+ DiffuseSampler->GetSample(0, 0) * Math::Max(lDotN, 0.0f);

	return Math::Min(color, 1.0f);
}


//-----------------------------------------------------------------------------

PhongShader::PhongShader(Sampler *ambient, Sampler *diffuse, Sampler *specular, const float shininess)
	: AmbientSampler(ambient),
	DiffuseSampler(diffuse),
	SpecularSampler(specular),
	Shininess(shininess)
{
}

PhongShader::~PhongShader()
{
}

Vector3 PhongShader::GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light)
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
	else
	{
		lDotN = 0.0f;
	}

	Vector3 color = AmbientSampler->GetSample(0, 0)
		+ DiffuseSampler->GetSample(0, 0) * lDotN
		+ SpecularSampler->GetSample(0, 0) * Math::Clamp(spec, 0.0f, 1.0f);

	return Math::Min(color, 1.0f);
}


} // ~ namespace LumixRayTracer
