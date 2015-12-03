#include "light.h"


namespace LumixRayTracer
{

PointLight::PointLight()
	: _position(0.0f, 0.0f, 0.0f)
{ }

PointLight::PointLight(const Vector3 &position)
	: _position(position)
{
}

Vector3 PointLight::GetDirection(const Vector3& point) const
{
	return (point - _position).Normalized();
}

//-----------------------------------------------------------------------------

DirectionalLight::DirectionalLight()
	: _direction(0.0f, -1.0f, 0.0f)
{
}

DirectionalLight::DirectionalLight(const Vector3 &direction)
	: _direction(direction)
{
	_direction.Normalize();
}

Vector3 DirectionalLight::GetDirection(const Vector3& point) const
{
	return _direction;
}

} // ~ namespace LumixRayTracer
