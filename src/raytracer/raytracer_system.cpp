#include "raytracer_system.h"

#include "vector3.h"
#include "ray.h"
#include "ray_hit.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "collisions/collisions.h"

#include "renderer/texture.h"

#include "material.h"
#include "shading/lambert_shader.h"
#include "voxels/voxel_model.h"
#include "lightning/light.h"
#include "texturing/color_sampler.h"

#include "core/iallocator.h"
#include "core/free_list.h"

#include "core/MTJD/manager.h"
#include "core/MTJD/job.h"

#include "camera.h"


namespace LumixRayTracer
{
class TracingJob : public Lumix::MTJD::Job
{
private:
	Camera& _camera;
	VoxelModel* _model;
	Light* _light;
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
			   Light* light,
			   float deltaX,
			   float deltaY,
			   int startX,
			   int startY,
			   int iterCountX,
			   int iterCountY,
			   uint32_t* data,
			   Lumix::MTJD::Manager& manager,
			   Lumix::IAllocator& allocator,
			   Lumix::IAllocator& job_allocator)
			   : Lumix::MTJD::Job(Lumix::MTJD::Job::AUTO_DESTROY, Lumix::MTJD::Priority::Default, manager, allocator, job_allocator),
			   _camera(camera),
			   _model(model),
			   _light(light),
			   _deltaX(deltaX),
			   _deltaY(deltaY),
			   _startX(startX),
			   _startY(startY),
			   _iterCountX(iterCountX),
			   _iterCountY(iterCountY),
			   _data(data)
	{
		setJobName("TracingJob");
	}

	void execute() override
	{
		Ray ray;
		RayHit intersection;

		float relX = _startX * _deltaX;
		float relY = (_startY + _iterCountY) * _deltaY;
		int index = 0;

		for (int y = 0; y < _iterCountY; ++y)
		{
			relX = 0.0f;
			for (int x = 0; x < _iterCountX; ++x)
			{
				_camera.GetRay(relX, relY, ray);
				if (Intersections::RayAndVoxelGrid(ray, *_model, intersection))
				{
					Vector3 color = intersection.HitObject->ObjMaterial->MaterialShader->GetColor(intersection.Position, intersection.Normal, _camera, *_light);

					//shadow
					ray.Position = intersection.Position + intersection.Normal * 0.001f;
					ray.Direction = -_light->GetDirection(ray.Position);
					ray.MaxDistance = FLT_MAX;
					RayHit shadowHit;
					if (Intersections::RayAndVoxelGrid(ray, *_model, shadowHit))
					{
						color *= 0.0f;
					}
					
					_data[index] = (uint32_t)(color.x * 255)
						| (uint32_t)(color.y * 255) << 8
						| (uint32_t)(color.z * 255) << 16
						| 0xFF << 24;
				}
				else
				{
					_data[index] = (uint32_t)(Math::Abs(ray.Direction.x) * 100)
						| (uint32_t)(Math::Abs(ray.Direction.y) * 100) << 8
						| (uint32_t)(Math::Abs(ray.Direction.z) * 100) << 16
						| 0xFF << 24;
				}

				++index;
				relX += _deltaX;
			}

			relY -= _deltaY;
		}
	}
};

//-----------------------------------------------------------------------------

class RayTracerSystemImpl : public RayTracerSystem
{
private:
	Lumix::IAllocator& _allocator;
	Lumix::FreeList<TracingJob, 8> _job_allocator;
	Lumix::MTJD::Manager* _mtjd_manager;
	Lumix::MTJD::Group _sync_point;

	Camera _camera;
	Lumix::Texture* _texture;
	bool _isReady = false;

	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
	Material* _objectMaterial;
	VoxelModel* _voxelWord;
	Light* _light;
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //

public:
	RayTracerSystemImpl(Lumix::IAllocator& allocator)
		: _allocator(allocator),
		_job_allocator(_allocator),
		_mtjd_manager(Lumix::MTJD::Manager::create(allocator)),
		_sync_point(true, allocator)
	{
		// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
		ColorSampler* sampAmb = LUMIX_NEW(_allocator, ColorSampler)(Vector3(0.1f, 0.1f, 0.1f));
		ColorSampler* sampDiff = LUMIX_NEW(_allocator, ColorSampler)(Vector3(1.0f, 1.0f, 1.0f));
		LambertShader* shad = LUMIX_NEW(_allocator, LambertShader)(sampAmb, sampDiff);
		_objectMaterial = LUMIX_NEW(_allocator, Material)(shad);

		_voxelWord = LUMIX_NEW(_allocator, VoxelModel)(100, 10, 100);
		_voxelWord->ObjMaterial = _objectMaterial;

		_light = LUMIX_NEW(_allocator, DirectionalLight)(Vector3(-1, -2, -1).Normalized());
		// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
	}

	~RayTracerSystemImpl()
	{
		// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
		LambertShader* sh = static_cast<LambertShader*>(_objectMaterial->MaterialShader);
		LUMIX_DELETE(_allocator, sh->AmbientSampler);
		LUMIX_DELETE(_allocator, sh->DiffuseSampler);
		LUMIX_DELETE(_allocator, _objectMaterial->MaterialShader);
		LUMIX_DELETE(_allocator, _objectMaterial);
		LUMIX_DELETE(_allocator, _light);
		// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //

		Lumix::MTJD::Manager::destroy(*_mtjd_manager);
	}

	Lumix::IAllocator& getAllocator() { return _allocator; }

	virtual void SetTexture(Lumix::Texture* texture) override
	{
		_texture = texture;
	}

	virtual void Update(const float &deltaTime) override
	{
		if (!_isReady)
			return;

		ASSERT(_texture->getBytesPerPixel() == 4);

		int width = _texture->getWidth();
		int height = _texture->getHeight();
		int cpu_count = (int)_mtjd_manager->getCpuThreadsCount();
		int linesPerThread = (int)Math::Ceil(height / (float)cpu_count);

		uint32_t* data = (uint32_t*)(_texture->getData());

		Ray ray;
		RayHit intersection;

		float deltaX = 1.0f / width;
		float deltaY = 1.0f / height;

		int index = 0;
		TracingJob* jobs[4];

		for (int i = 0; i < cpu_count; ++i)
		{
			index = i * linesPerThread * height;

			TracingJob* tj = LUMIX_NEW(_job_allocator, TracingJob)(_camera,
																  _voxelWord,
																  _light,
																  deltaX,
																  deltaY,
																  0,
																  linesPerThread * (cpu_count - i - 1),
																  width,
																  linesPerThread,
																  &data[index],
																  *_mtjd_manager,
																  _allocator,
																  _job_allocator);
			tj->addDependency(&_sync_point);
			jobs[i] = tj;
		}

		for (int i = 0; i < cpu_count; ++i)
		{
			_mtjd_manager->schedule(jobs[i]);
		}

		_sync_point.sync();

		_texture->onDataUpdated(0, 0, width, height);
	}

	virtual Camera& GetCamera() override
	{
		return _camera;
	}

	virtual inline void SetIsReady(bool isReady) override
	{
		_isReady = isReady;
	}

	virtual inline bool GetIsReady() const override
	{
		return _isReady;
	}
};

//-----------------------------------------------------------------------------

RayTracerSystem* RayTracerSystem::create(Lumix::IAllocator& allocator)
{
	return LUMIX_NEW(allocator, RayTracerSystemImpl)(allocator);
}


void RayTracerSystem::destroy(RayTracerSystem& rayTracerSystem)
{
	LUMIX_DELETE(static_cast<RayTracerSystemImpl&>(rayTracerSystem).getAllocator(), &rayTracerSystem);
}

} // ~namespace LumixRayTracer
