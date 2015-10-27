#pragma once


namespace LumixRayTracer
{
struct Vector3;

class Shader
{
public:

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Vector3 &camera, const Vector3 &light)
	{
		return Vector3();
	}
};

} // ~ namespace LumixRayTracer
