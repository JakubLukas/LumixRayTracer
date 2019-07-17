#include "editor/studio_app.h"
#include "editor/world_editor.h"


using namespace Lumix;

namespace
{

	struct StudioAppPlugin : StudioApp::IPlugin
	{
		StudioAppPlugin(StudioApp& app)
			: m_app(app)
		{}

		void init() override {}
		const char* getName() const override { return "raytracer"; }

		StudioApp& m_app;
	};

}

LUMIX_STUDIO_ENTRY(LumixRayTracer)
{
	IAllocator& allocator = app.getWorldEditor().getAllocator();
	return LUMIX_NEW(allocator, StudioAppPlugin)(app);
}
