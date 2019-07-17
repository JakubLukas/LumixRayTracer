#include "raytracer_plugin.h"

#include "engine/engine.h"
#include "engine/allocator.h"

namespace Lumix
{


struct RayTracerPluginImpl : public RayTracerPlugin
{
	Engine& _engine;

	RayTracerPluginImpl(Engine& engine)
		: _engine(engine)
	{
	}

	~RayTracerPluginImpl()
	{
	}

	const char* getName() const { return "LumixRayTracer"; };
};


LUMIX_PLUGIN_ENTRY(LumixRayTracer)
{
	return LUMIX_NEW(engine.getAllocator(), RayTracerPluginImpl)(engine);
}


} // namespace Lumix
