#include "raytracer.h"

#include "core/array.h"
#include "core/crc32.h"
#include "core/fs/file_system.h"
#include "core/json_serializer.h"
#include "core/lifo_allocator.h"
#include "core/math_utils.h"
#include "core/profiler.h"
#include "core/resource_manager.h"
#include "core/resource_manager_base.h"
#include "core/vec4.h"
#include "debug/allocator.h"
#include "debug/debug.h"
#include "editor/world_editor.h"
#include "engine.h"
#include "engine/property_descriptor.h"
#include "renderer/material.h"
#include "renderer/material_manager.h"
#include "renderer/model.h"
#include "renderer/model_manager.h"
#include "renderer/pipeline.h"
#include "renderer/render_scene.h"
#include "renderer/shader.h"
#include "renderer/shader_manager.h"
#include "renderer/texture.h"
#include "renderer/texture_manager.h"
#include "universe/universe.h"
#include <bgfx/bgfx.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdio>

namespace LumixRayTracer
{
	struct RayTracerImpl : public RayTracer
	{
		typedef char ShaderDefine[32];

		Lumix::Engine& m_engine;


		RayTracerImpl(Lumix::Engine& engine)
			: m_engine(engine)
		{

		}

		~RayTracerImpl()
		{

		}

		virtual bool create() override { return true; }

		virtual void destroy() override {}

		virtual const char* getName() const override { return "raytracer"; }

		virtual Lumix::Engine& getEngine() override { return m_engine; }
	};

} // ~namespace LumixRayTracer

namespace Lumix
{

extern "C" Lumix::IPlugin* createPlugin(Lumix::Engine& engine)
{
	return engine.getAllocator().newObject<LumixRayTracer::RayTracerImpl>(engine);
	Lumix::g_log_info.log("raytracer") << "RayTracer plugin loaded";
}

} // ~namespace Lumix
