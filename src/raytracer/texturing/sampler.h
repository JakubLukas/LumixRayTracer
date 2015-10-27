#pragma once


namespace LumixRayTracer
{
class Vector3;

class Sampler
{
public:

	virtual Vector3 GetSample(float x, float y)
	{
		return Vector3();
	};

};

} // ~ namespace LumixRayTracer