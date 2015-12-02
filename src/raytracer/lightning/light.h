#pragma once

#include "vector3.h"


namespace LumixRayTracer
{

class Light
{
public:
	virtual const Vector3& GetDirection(const Vector3& point) const = 0;
};

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

class DirectionalLight : public Light
{
private:
	Vector3 _direction;

public:
	DirectionalLight()
		: _direction(0.0f, -1.0f, 0.0f)
	{ }

	DirectionalLight(const Vector3 &direction)
		: _direction(direction)
	{
		_direction.Normalize();
	}

	virtual const Vector3& GetDirection(const Vector3& point) const override
	{
		return _direction;
	}
};

} // ~ namespace LumixRayTracer
