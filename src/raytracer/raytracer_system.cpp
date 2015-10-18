#include "raytracer_system.h"

#include "core/array.h"
#include "core/crc32.h"
#include "core/path.h"
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
#include "engine/plugin_manager.h"
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

#include "raytracer.h"

namespace LumixRayTracer
{
	static const char* MATERIAL_PATH = "models/raytracer/raytracer.mat";
	static const char* TEXTURE_PATH = "models/raytracer/raytracer.tga";

	struct RayTracerSystemImpl : public RayTracerSystem
	{
		Lumix::Engine& _engine;
		Lumix::WorldEditor* _editor;

		Lumix::Texture* _texture;
		bool _textureLoaded = false;

		RayTracer rayTracer;

		RayTracerSystemImpl(Lumix::Engine& engine)
			: _engine(engine), _editor(nullptr)
		{

		}

		~RayTracerSystemImpl()
		{

		}

		virtual bool create() override
		{
			{
				auto* manager = _engine.getResourceManager().get(Lumix::ResourceManager::TEXTURE);
				Lumix::TextureManager* tex_manager = static_cast<Lumix::TextureManager*>(manager);

				auto* resource = tex_manager->load(Lumix::Path(TEXTURE_PATH));
				_texture = static_cast<Lumix::Texture*>(resource);
				_texture->addDataReference();
				_texture->onLoaded<RayTracerSystemImpl, &RayTracerSystemImpl::onTextureLoaded>(this);
			}

			{
				auto* manager = _engine.getResourceManager().get(Lumix::ResourceManager::PIPELINE);
				Lumix::PipelineManager* pip_manager = static_cast<Lumix::PipelineManager*>(manager);

				auto* resource = pip_manager->get(Lumix::Path("pipelines/main.lua"));
				Lumix::Pipeline* pipline = static_cast<Lumix::Pipeline*>(resource);
			}
			return true;
		}

		virtual void destroy() override
		{
			if (_texture != nullptr)
				_texture->removeDataReference();
		}

		void onTextureLoaded(Lumix::Resource::State, Lumix::Resource::State new_state)
		{
			_textureLoaded = (new_state == Lumix::Resource::State::READY);
		}

		virtual void update(float deltaTime) override
		{
			if (!_textureLoaded || _editor == nullptr) return;

			updateCamera();

			int m_y = 0;
			int m_x = 0;
			int m_width = 32;
			int m_height = 23;

			int bpp = _texture->getBytesPerPixel();

			for (int j = m_y; j < m_y + m_height; ++j)
			{
				for (int i = m_x; i < m_x + m_width; ++i)
				{
					int index = bpp * (i + j * _texture->getWidth());
					for (int k = 0; k < bpp; ++k)
					{
						_texture->getData()[index + k] = 100;
					}
				}
			}
			_texture->onDataUpdated(m_x, m_y, m_width, m_height);
		}

		void updateCamera()
		{
			auto* render_scene = static_cast<Lumix::RenderScene*>(_editor->getScene(Lumix::crc32("renderer")));
			Lumix::Entity camera = render_scene->getCameraEntity(render_scene->getCameraInSlot("editor"));
			Lumix::ComponentUID id = _editor->getComponent(camera, Lumix::crc32("camera"));

			Lumix::Vec3 pos = _editor->getUniverse()->getPosition(camera);
			Lumix::Quat rot = _editor->getUniverse()->getRotation(camera);
			float fov = render_scene->getCameraFOV(id.index);
			int width = render_scene->getCameraWidth(id.index);
			int height = render_scene->getCameraHeight(id.index);
			int nearPlane = render_scene->getCameraNearPlane(id.index);
			int farPlane = render_scene->getCameraFarPlane(id.index);
			Lumix::Matrix mat = _editor->getUniverse()->getMatrix(camera);

			rayTracer.UpdateCamera(pos, rot, fov, width, height, nearPlane, farPlane, mat);
		}

		virtual void setWorldEditor(Lumix::WorldEditor& editor) override
		{
			_editor = &editor;
		}

		virtual Lumix::WorldEditor* getWorldEditor()
		{
			return _editor;
		}

		virtual Lumix::Engine& getEngine() override
		{
			return _engine;
		}

		virtual const char* getName() const override
		{
			return PLUGIN_NAME;
		}
	};

} // ~namespace LumixRayTracer


extern "C" Lumix::IPlugin* createPlugin(Lumix::Engine& engine)
{
	return LUMIX_NEW(engine.getAllocator(), LumixRayTracer::RayTracerSystemImpl)(engine);
}

extern "C" void setWorldEditor(Lumix::WorldEditor& editor)
{
	Lumix::IPlugin* plugin = editor.getEngine().getPluginManager().getPlugin(LumixRayTracer::PLUGIN_NAME);
	LumixRayTracer::RayTracerSystem* tracer = static_cast<LumixRayTracer::RayTracerSystem*>(plugin);
	tracer->setWorldEditor(editor);
}
