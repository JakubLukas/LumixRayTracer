#include "editor/studio_app.h"
#include "editor/world_editor.h"
#include "editor/utils.h"

#include "imgui/imgui.h"


using namespace Lumix;

namespace
{

	struct RaytracerViewPlugin : StudioApp::GUIPlugin
	{
		RaytracerViewPlugin(StudioApp& app)
		{
			WorldEditor& editor = app.getWorldEditor();
			Action* action = LUMIX_NEW(editor.getAllocator(), Action)("Raytracer View", "Toggle raytracer view", "raytracer_view");
			action->func.bind<RaytracerViewPlugin, &RaytracerViewPlugin::onAction>(this);
			action->is_selected.bind<RaytracerViewPlugin, &RaytracerViewPlugin::isOpen>(this);
			app.addWindowAction(action);
		}

		virtual ~RaytracerViewPlugin() {}

		void onWindowGUI() override
		{
			if (!m_is_open) return;

			const char* window_name = "Raytracer View###raytracer_view";
			if (ImGui::Begin(window_name, &m_is_open, ImGuiWindowFlags_NoNavInputs))
			{

			}
			ImGui::End();
		}

		virtual bool hasFocus() { return false; }
		virtual void update(float) {}
		virtual const char* getName() const { return "raytracer_view"; }
		virtual void guiEndFrame() {}

		void onSettingsLoaded() override
		{
			//m_is_open = m_app.getSettings().getValue("is_raytracer_view_open", false);
		}
		void onBeforeSettingsSaved() override
		{
			//m_app.getSettings().setValue("is_raytracer_view_open", m_is_open);
		}

		bool isOpen() const { return m_is_open; }
		void onAction() { m_is_open = !m_is_open; }


		bool m_is_open = false;
	};

	struct StudioAppPlugin : StudioApp::IPlugin
	{
		StudioAppPlugin(StudioApp& app)
			: m_app(app)
		{}

		~StudioAppPlugin()
		{
			IAllocator& allocator = m_app.getWorldEditor().getAllocator();

			m_app.removePlugin(*m_raytracer_view_plugin);
			LUMIX_DELETE(allocator, m_raytracer_view_plugin);
		}

		void init() override
		{
			IAllocator& allocator = m_app.getWorldEditor().getAllocator();

			m_raytracer_view_plugin = LUMIX_NEW(allocator, RaytracerViewPlugin)(m_app);
			m_app.addPlugin(*m_raytracer_view_plugin);
		}
		
		const char* getName() const override { return "raytracer"; }


		StudioApp& m_app;
		RaytracerViewPlugin* m_raytracer_view_plugin = nullptr;
	};

}

LUMIX_STUDIO_ENTRY(LumixRayTracer)
{
	IAllocator& allocator = app.getWorldEditor().getAllocator();
	return LUMIX_NEW(allocator, StudioAppPlugin)(app);
}
