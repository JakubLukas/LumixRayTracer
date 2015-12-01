#pragma once

#include "light.h"
#include "vector3.h"

namespace LumixRayTracer
{
	struct Vector3;

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
