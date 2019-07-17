#pragma once

#include "engine/iplugin.h"


namespace Lumix
{

class RayTracerPlugin : public IPlugin
{
	const char* getName() const = 0;
};


}
