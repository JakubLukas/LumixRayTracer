#pragma once

#include "vector3.h"
#include "shading/shader.h"


namespace LumixRayTracer
{

class Object
{
protected:
	Shader _shader;
	Vector3 _position;

public:
	Object()
		: _position(0.0f, 0.0f, 0.0f)
	{}

	inline 
};

} // ~ namespace LumixRayTracer
