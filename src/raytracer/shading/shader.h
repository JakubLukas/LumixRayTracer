#pragma once


namespace LumixRayTracer
{
struct Vector3;
class Camera;
class Light;
class Sampler;

//-----------------------------------------------------------------------------

class Shader
{
public:
	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light);
};

//-----------------------------------------------------------------------------

class LambertShader : public Shader
{
public:
	Sampler* AmbientSampler;
	Sampler* DiffuseSampler;

public:
	LambertShader(Sampler *ambient, Sampler *diffuse);
	~LambertShader();

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light) override;
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
	PhongShader(Sampler *ambient, Sampler *diffuse, Sampler *specular, const float shininess);
	~PhongShader();

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const Light &light) override;
};

} // ~ namespace LumixRayTracer
