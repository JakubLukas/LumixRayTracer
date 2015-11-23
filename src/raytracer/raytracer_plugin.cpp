#include "raytracer_plugin.h"

#include "core/crc32.h"
#include "core/resource_manager.h"
#include "editor/world_editor.h"
#include "engine.h"
#include "engine/plugin_manager.h"
#include "renderer/material.h"
#include "renderer/material_manager.h"
#include "renderer/render_scene.h"
#include "renderer/texture.h"
#include "renderer/texture_manager.h"
#include "universe/universe.h"

#include "raytracer_system.h"
#include "camera.h"

namespace LumixRayTracer
{

static const char* MATERIAL_PATH = "models/raytracer/raytracer.mat";
static const char* TEXTURE_PATH = "models/raytracer/raytracer.tga";

static const uint32_t RENDERER_CRC = Lumix::crc32("renderer");
static const uint32_t EDITOR_CRC = Lumix::crc32("editor");
static const uint32_t CAMERA_CRC = Lumix::crc32("camera");

struct RayTracerPluginImpl : public RayTracerPlugin
{
	Lumix::Engine& _engine;
	Lumix::WorldEditor* _editor;

	Lumix::Material* _material;
	Lumix::Texture* _texture;
	Lumix::ComponentUID cameraUid;

	RayTracerSystem* rayTracerSystem;

	RayTracerPluginImpl(Lumix::Engine& engine)
		: _engine(engine),
		_editor(nullptr),
		_material(nullptr),
		_texture(nullptr),
		cameraUid(Lumix::ComponentUID::INVALID)
	{
		rayTracerSystem = RayTracerSystem::create(engine.getAllocator());
	}

	~RayTracerPluginImpl()
	{
		RayTracerSystem::destroy(*rayTracerSystem);
	}


	virtual bool create() override
	{
		loadMaterial();
		return true;
	}

	virtual void destroy() override
	{
		unloadMaterial();
		unloadTexture();
	}

	virtual const char* getName() const override
	{
		return PLUGIN_NAME;
	}

	void loadMaterial()
	{
		auto* manager = _engine.getResourceManager().get(Lumix::ResourceManager::MATERIAL);
		Lumix::MaterialManager* mat_manager = static_cast<Lumix::MaterialManager*>(manager);

		auto* resource = mat_manager->load(Lumix::Path(MATERIAL_PATH));
		_material = static_cast<Lumix::Material*>(resource);
		_material->onLoaded<RayTracerPluginImpl, &RayTracerPluginImpl::onMaterialLoaded>(this);
	}

	void unloadMaterial()
	{
		if (_material == nullptr) return;

		auto* manager = _engine.getResourceManager().get(Lumix::ResourceManager::MATERIAL);
		Lumix::MaterialManager* mat_manager = static_cast<Lumix::MaterialManager*>(manager);
		mat_manager->unload(Lumix::Path(MATERIAL_PATH));
	}

	void loadTexture()
	{
		ASSERT(_material != nullptr);
		ASSERT(_material->getTextureCount() > 0);
		if (_texture == _material->getTexture(0)) return;

		_texture = _material->getTexture(0);
		_texture->addDataReference();
		_texture->onLoaded<RayTracerPluginImpl, &RayTracerPluginImpl::onTextureLoaded>(this);
		rayTracerSystem->SetTexture(_texture);
	}

	void unloadTexture()
	{
		if (_texture == nullptr) return;

		_texture->removeDataReference();
		auto* manager = _engine.getResourceManager().get(Lumix::ResourceManager::TEXTURE);
		Lumix::TextureManager* tex_manager = static_cast<Lumix::TextureManager*>(manager);
		tex_manager->unload(Lumix::Path(TEXTURE_PATH));
	}


	void onMaterialLoaded(Lumix::Resource::State, Lumix::Resource::State new_state)
	{
		switch (new_state)
		{
			case Lumix::Resource::State::EMPTY:
				rayTracerSystem->SetIsReady(false);
				break;
			case Lumix::Resource::State::READY:
				loadTexture();
				break;
			default:
				ASSERT(false);
				break;
		}
	}

	void onTextureLoaded(Lumix::Resource::State, Lumix::Resource::State new_state)
	{
		switch (new_state)
		{
			case Lumix::Resource::State::EMPTY:
				rayTracerSystem->SetIsReady(false);
				break;
			case Lumix::Resource::State::READY:
				rayTracerSystem->SetIsReady(true);
				break;
			default:
				ASSERT(false);
				break;
		}
	}


	virtual void update(float deltaTime) override
	{
		if (_editor == nullptr) return;

		updateCamera();
		rayTracerSystem->Update(deltaTime);
	}

	void updateCamera()
	{
		auto* renderScene = static_cast<Lumix::RenderScene*>(_editor->getScene(LumixRayTracer::RENDERER_CRC));
		Camera& cam = rayTracerSystem->GetCamera();

		cam.Position = _editor->getUniverse()->getPosition(cameraUid.entity);
		cam.Rotation = _editor->getUniverse()->getRotation(cameraUid.entity);
		cam.FOV = renderScene->getCameraFOV(cameraUid.index);
		cam.Width = renderScene->getCameraWidth(cameraUid.index);
		cam.Height = renderScene->getCameraHeight(cameraUid.index);
		cam.NearPlane = renderScene->getCameraNearPlane(cameraUid.index);
		cam.FarPlane = renderScene->getCameraFarPlane(cameraUid.index);
		cam.OnChanged();
	}


	virtual void setWorldEditor(Lumix::WorldEditor& editor) override
	{
		_editor = &editor;

		auto* renderScene = static_cast<Lumix::RenderScene*>(editor.getScene(LumixRayTracer::RENDERER_CRC));

		Lumix::Entity camera = renderScene->getCameraEntity(renderScene->getCameraInSlot("editor"));
		cameraUid = editor.getComponent(camera, LumixRayTracer::CAMERA_CRC);
	}

	virtual Lumix::WorldEditor* getWorldEditor()
	{
		return _editor;
	}

	virtual Lumix::Engine& getEngine() override
	{
		return _engine;
	}
};

} // ~namespace LumixRayTracer


extern "C" Lumix::IPlugin* createPlugin(Lumix::Engine& engine)
{
	return LUMIX_NEW(engine.getAllocator(), LumixRayTracer::RayTracerPluginImpl)(engine);
}

extern "C" void setWorldEditor(Lumix::WorldEditor& editor)
{
	Lumix::IPlugin* plugin = editor.getEngine().getPluginManager().getPlugin(LumixRayTracer::PLUGIN_NAME);
	LumixRayTracer::RayTracerPlugin* rayTracerPlugin = static_cast<LumixRayTracer::RayTracerPlugin*>(plugin);

	auto* render_scene = static_cast<Lumix::RenderScene*>(editor.getScene(LumixRayTracer::RENDERER_CRC));
	Lumix::Entity camera = render_scene->getCameraEntity(render_scene->getCameraInSlot("editor"));

	rayTracerPlugin->setWorldEditor(editor);
}
