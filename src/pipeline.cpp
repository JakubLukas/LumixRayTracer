//"public: static class Lumix::Pipeline * __cdecl Lumix::Pipeline::create(class Lumix::Renderer &,class Lumix::Path const &,struct Lumix::IAllocator &)" (? create@Pipeline@Lumix@@SAPEAV12@AEAVRenderer@2@AEBVPath@2@AEAUIAllocator@2@@Z) referenced in function "public: void __cdecl Lumix::App::init(void)" (? init@App@Lumix@@QEAAXXZ)	app	D : \projects\LumixEngine\projects\tmp\vs2015\main_win.obj	1

/*#include "pipeline.h"


namespace Lumix
{


class PipelineImpl : public Pipeline
{
public:
};


Pipeline* Pipeline::create(RayTracerPlugin& renderer, const Path& path, IAllocator& allocator)
{
	return LUMIX_NEW(allocator, PipelineImpl)(renderer, path, allocator);
}


void Pipeline::destroy(Pipeline* pipeline)
{
	LUMIX_DELETE(static_cast<PipelineImpl*>(pipeline)->m_allocator, pipeline);
}


}*/
