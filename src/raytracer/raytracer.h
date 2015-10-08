#pragma once


#include "lumix.h"
#include "iplugin.h"

namespace LumixRayTracer
{


class LUMIX_LIBRARY_EXPORT RayTracer : public Lumix::IPlugin
{
	virtual Lumix::Engine& getEngine() = 0;
};


} // ~ namespace LumixRayTracer

namespace Lumix
{

	extern "C" {
		LUMIX_LIBRARY_EXPORT IPlugin* createPlugin(Engine& engine);
	}

} // ~ namespace Lumix