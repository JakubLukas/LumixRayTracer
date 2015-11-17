#pragma once


namespace LumixRayTracer
{
struct Vector3;
class DirectionalLight;

class Shader
{
public:

	virtual Vector3 GetColor(const Vector3 &point, const Vector3 &normal, const Camera &camera, const DirectionalLight &light)
	{
		return Vector3();
	}
};

} // ~ namespace LumixRayTracer
