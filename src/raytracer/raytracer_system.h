#pragma once

#include "Debug/allocator.h"
#include "core/free_list.h"

#include "core/MTJD/manager.h"
#include "core/MTJD/job.h"

#include "camera.h"


namespace Lumix
{
class Texture;
}

namespace LumixRayTracer
{
class Material;
class VoxelModel;
class DirectionalLight;




class TracingJob : public Lumix::MTJD::Job
{
private:
	Camera& _camera;
	VoxelModel* _model;
	DirectionalLight* _light;
	float _deltaX;
	float _deltaY;
	int _startX;
	int _startY;
	int _iterCountX;
	int _iterCountY;
	uint32_t* _data;

public:
	TracingJob(Camera& camera,
			   VoxelModel* model,
			   DirectionalLight* light,
			   float deltaX,
			   float deltaY,
			   int startX,
			   int startY,
			   int iterCountX,
			   int iterCountY,
			   uint32_t* data,
			   Lumix::MTJD::Manager& manager,
			   Lumix::IAllocator& allocator,
			   Lumix::IAllocator& job_allocator);

	void execute() override;
};

//-----------------------------------------------------------------------------

class RayTracerSystem
{
private:
	Lumix::Debug::Allocator _allocator;
	Lumix::FreeList<TracingJob, 8> _job_allocator;
	Lumix::MTJD::Manager _mtjd_manager;
	Lumix::MTJD::Group _sync_point;

	Camera _camera;
	Lumix::Texture* _texture;
	bool _isReady = false;

	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
	Material* _objectMaterial;
	VoxelModel* _voxelWord;
	DirectionalLight* _light;
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //

public:
	RayTracerSystem(Lumix::IAllocator& allocator);
	~RayTracerSystem();

	void SetTexture(Lumix::Texture* texture);

	void Update(const float &deltaTime);
	void UpdateCamera(const Lumix::Vec3 &position,
		const Lumix::Quat &rotation,
		const float &fov,
		const float &width,
		const float &height,
		const float &nearPlane,
		const float &farPlane,
		const Lumix::Matrix& viewMatrix);

	inline void SetIsReady(bool isReady);
	inline bool GetIsReady() const;
};

inline void RayTracerSystem::SetIsReady(bool isReady)
{
	_isReady = isReady;
}

inline bool RayTracerSystem::GetIsReady() const
{
	return _isReady;
}

} // ~ namespace LumixRayTracer
