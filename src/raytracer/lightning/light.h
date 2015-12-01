#pragma once


namespace LumixRayTracer
{
struct Vector3;

class Light
{
public:
	virtual const Vector3& GetDirection(const Vector3& point) const = 0;
};

} // ~ namespace LumixRayTracer
