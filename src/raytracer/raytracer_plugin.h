#pragma once


#include "lumix.h"
#include "iplugin.h"

namespace Lumix
{
	class WorldEditor;
}


namespace LumixRayTracer
{

static const char* PLUGIN_NAME = "RayTracer";

class LUMIX_LIBRARY_EXPORT RayTracerPlugin : public Lumix::IPlugin
{
	virtual Lumix::WorldEditor* getWorldEditor() = 0;
	virtual Lumix::Engine& getEngine() = 0;

public:
	virtual void setWorldEditor(Lumix::WorldEditor& editor) = 0;
};

} // ~ namespace LumixRayTracer


extern "C"
{
	LUMIX_LIBRARY_EXPORT Lumix::IPlugin* createPlugin(Lumix::Engine& engine);
}

extern "C"
{
	LUMIX_LIBRARY_EXPORT void setWorldEditor(Lumix::WorldEditor& editor);
}
