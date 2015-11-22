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
#include "lightning/directional_light.h"


namespace LumixRayTracer
{

TracingJob::TracingJob(Camera& camera,
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

void TracingJob::execute()
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
				uint8_t tmp[4] = { (uint8_t)(color.x * 255), (uint8_t)(color.y * 255), (uint8_t)(color.z * 255), 0xFF };
				_data[index] = *(uint32_t*)(tmp);
			}
			else
			{
				uint8_t tmp[4] = { (uint8_t)(Math::Abs(ray.Direction.x) * 100), (uint8_t)(Math::Abs(ray.Direction.y) * 100), (uint8_t)(Math::Abs(ray.Direction.z) * 100), 0xFF };
				_data[index] = *(uint32_t*)(tmp);
			}

			++index;
			relX += _deltaX;
		}

		relY -= _deltaY;
	}
}

//-----------------------------------------------------------------------------

RayTracerSystem::RayTracerSystem(Lumix::IAllocator& allocator)
	: _allocator(allocator),
	_job_allocator(_allocator),
	_mtjd_manager(allocator),
	_sync_point(true, allocator)
{
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
	ColorSampler* sampAmb = LUMIX_NEW(_allocator, ColorSampler)(Vector3(0.05f, 0.05f, 0.05f));
	ColorSampler* sampDiff = LUMIX_NEW(_allocator, ColorSampler)(Vector3(1.0f, 1.0f, 1.0f));
	LambertShader* shad = LUMIX_NEW(_allocator, LambertShader)(sampAmb, sampDiff);
	_objectMaterial = LUMIX_NEW(_allocator, Material)(shad);

	_voxelWord = LUMIX_NEW(_allocator, VoxelModel)(10, 10, 10);
	_voxelWord->ObjMaterial = _objectMaterial;

	_light = LUMIX_NEW(_allocator, DirectionalLight)(Vector3(-1, -1, -1));
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
}

RayTracerSystem::~RayTracerSystem()
{
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
	LambertShader* sh = static_cast<LambertShader*>(_objectMaterial->MaterialShader);
	LUMIX_DELETE(_allocator, sh->AmbientSampler);
	LUMIX_DELETE(_allocator, sh->DiffuseSampler);
	LUMIX_DELETE(_allocator, _objectMaterial->MaterialShader);
	LUMIX_DELETE(_allocator, _objectMaterial);
	LUMIX_DELETE(_allocator, _light);
	// TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP // TEMP //
}

void RayTracerSystem::SetTexture(Lumix::Texture* texture)
{
	_texture = texture;
}

void RayTracerSystem::Update(const float &deltaTime)
{
	if (!_isReady)
		return;

	ASSERT(_texture->getBytesPerPixel() == 4);
	int width = _texture->getWidth();
	int height = _texture->getHeight();
	uint32_t* data = (uint32_t*)(_texture->getData());
	int cpu_count = (int)_mtjd_manager.getCpuThreadsCount();

	Ray ray;
	RayHit intersection;
	
	float deltaX = 1.0f / width;
	float deltaY = 1.0f / height;

	int index = 0;
	TracingJob* jobs[4];

	for (int i = 0; i < cpu_count; ++i)
	{
		index = i * 64 * height;

		TracingJob* tj = _job_allocator.newObject<TracingJob>(_camera,
															  _voxelWord,
															  _light,
															  deltaX,
															  deltaY,
															  0,
															  64 * (cpu_count - i - 1),
															  width,
															  64,
															  &data[index],
															  _mtjd_manager,
															  _allocator,
															  _job_allocator);
		tj->addDependency(&_sync_point);
		jobs[i] = tj;
	}

	for (int i = 0; i < cpu_count; ++i)
	{
		_mtjd_manager.schedule(jobs[i]);
	}

	_sync_point.sync();

	_texture->onDataUpdated(0, 0, width, height);
}

void RayTracerSystem::UpdateCamera(const Lumix::Vec3 &position,
	const Lumix::Quat &rotation,
	const float &fov,
	const float &width,
	const float &height,
	const float &nearPlane,
	const float &farPlane,
	const Lumix::Matrix& viewMatrix)
{
	_camera.Position = position;
	_camera.Rotation = rotation;
	_camera.FOV = fov;
	_camera.Width = width;
	_camera.Height = height;
	_camera.NearPlane = nearPlane;
	_camera.FarPlane = farPlane;
	_camera.OnChanged();
}

} // ~namespace LumixRayTracer
