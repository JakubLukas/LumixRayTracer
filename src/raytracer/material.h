#pragma once

#include "shading/shader.h"


namespace LumixRayTracer
{

class Material
{
public:
	Shader* MaterialShader;

	Material()
		: MaterialShader(nullptr)
	{ }

	Material(Shader* shader)
		: MaterialShader(shader)
	{ }
};

} // ~ namespace LumixRayTracer
