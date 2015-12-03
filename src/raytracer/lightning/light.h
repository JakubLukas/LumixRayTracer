#pragma once

#include "vector3.h"


namespace LumixRayTracer
{
	struct Vector3;

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
	PointLight();
	PointLight(const Vector3 &position);

	virtual const Vector3& GetDirection(const Vector3& point) const override;
};

//-----------------------------------------------------------------------------

class DirectionalLight : public Light
{
private:
	Vector3 _direction;

public:
	DirectionalLight();
	DirectionalLight(const Vector3 &direction);

	virtual const Vector3& GetDirection(const Vector3& point) const override;
};

} // ~ namespace LumixRayTracer
