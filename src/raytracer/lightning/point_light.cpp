#pragma once

#include "light.h"
#include "vector3.h"

namespace LumixRayTracer
{

class PointLight : public Light
{
private:
	Vector3 _position;

public:
	PointLight()
		: _position(0.0f, 0.0f, 0.0f)
	{ }

	PointLight(const Vector3 &position)
		: _position(position)
	{
		_position.Normalize();
	}

	virtual const Vector3& GetDirection(const Vector3& point) const override
	{
		return point - _position;
	}
};

} // ~ namespace LumixRayTracer
