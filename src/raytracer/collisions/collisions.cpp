#include "collisions.h"

#include <cfloat>
#include "ray.h"
#include "ray_hit.h"
#include "primitives/sphere.h"
#include "primitives/box.h"
#include "voxels/voxel_model.h"
#include "math_rt.h"


namespace LumixRayTracer
{

namespace Intersections
{

bool RayAndSphere(const Ray &ray, const Sphere &sphere, RayHit &intersection)
{
	Vector3 vpc = sphere.Position - ray.Position;

	if (Vector3::Dot(vpc, ray.Direction) < 0.0f) // when the sphere is behind the origin p
	{
		// note that this case may be dismissed if it is considered that p is outside the sphere 	
		if (vpc.length() > sphere.Radius)
		{
			return false;// there is no intersection
		}
		else if (vpc.length() == sphere.Radius)
		{
			intersection.Position = ray.Position;
		}
		else // occurs when p is inside the sphere
		{
			Vector3 pc = ray.Position + ray.Direction * Vector3::Dot(ray.Direction, vpc) / ray.Direction.length();//projection of c on the line
				// distance from pc to i1
			float dist = Math::Sqrt(sphere.Radius*sphere.Radius - (pc - sphere.Position).length()*(pc - sphere.Position).length());
			float di1 = dist - (pc - ray.Position).length();
			if (di1 > ray.MaxDistance)
				return false;

			intersection.Position = ray.Position + ray.Direction * di1;
			
		}
	}
	else // center of sphere projects on the ray
	{
		Vector3 pc = ray.Position + ray.Direction * Vector3::Dot(ray.Direction, vpc) / ray.Direction.length();//projection of c on the line
		if ((sphere.Position - pc).length() > sphere.Radius)
		{
			return false;// there is no intersection
		}
		else
		{
			// distance from pc to i1
			float dist = Math::Sqrt(Math::Pow(sphere.Radius, 2.0f) - Math::Pow((pc - sphere.Position).length(), 2.0f));
			float diDist = ((vpc.length() > sphere.Radius) ? -1 : 1) * dist;// -dist if origin is outside sphere else +dist
			float di1 = (pc - ray.Position).length() + diDist;
			if (di1 > ray.MaxDistance)
				return false;

			intersection.Position = ray.Position + ray.Direction * di1;
		}
	}
	intersection.Normal = intersection.Position - sphere.Position;
	intersection.Normal.normalize();
	intersection.HitObject = (Model*)&sphere;

	return true;
}

bool RayAndBox(const Ray &ray, const Box &box, RayHit &intersection)
{
	static const float EPSILON = FLT_EPSILON;

	Vector3 boxMax = box.Position + box.Size;
	float t[6] = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f };

	if (ray.Direction.x > EPSILON || ray.Direction.x < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.x;
		t[0] = (box.Position.x - ray.Position.x) * dirfrac;
		t[1] = (boxMax.x - ray.Position.x) * dirfrac;
	}

	if (ray.Direction.y > EPSILON || ray.Direction.y < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.y;
		t[2] = (box.Position.y - ray.Position.y) * dirfrac;
		t[3] = (boxMax.y - ray.Position.y) * dirfrac;
	}

	if (ray.Direction.z > EPSILON || ray.Direction.z < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.z;
		t[4] = (box.Position.z - ray.Position.z) * dirfrac;
		t[5] = (boxMax.z - ray.Position.z) * dirfrac;
	}

	float tmin = Math::Max(Math::Min(t[0], t[1]), Math::Min(t[2], t[3]), Math::Min(t[4], t[5]));
	float tmax = Math::Min(Math::Max(t[0], t[1]), Math::Max(t[2], t[3]), Math::Max(t[4], t[5]));

	if (tmax < 0.0f || tmin > tmax || tmin > ray.MaxDistance) // box is behind
		return false;

	intersection.Position = ray.Position + ray.Direction * tmin;

	if (Math::Abs(intersection.Position.x - box.Position.x) < EPSILON)
		intersection.Normal = Vector3(-1.0f, 0.0f, 0.0f);
	else if (Math::Abs(intersection.Position.x - boxMax.x) < EPSILON)
		intersection.Normal = Vector3(1.0f, 0.0f, 0.0f);
	else if (Math::Abs(intersection.Position.y - box.Position.y) < EPSILON)
		intersection.Normal = Vector3(0.0f, -1.0f, 0.0f);
	else if (Math::Abs(intersection.Position.y - boxMax.y) < EPSILON)
		intersection.Normal = Vector3(0.0f, 1.0f, 0.0f);
	else if (Math::Abs(intersection.Position.z - box.Position.z) < EPSILON)
		intersection.Normal = Vector3(0.0f, 0.0f, -1.0f);
	else if (Math::Abs(intersection.Position.z - boxMax.z) < EPSILON)
		intersection.Normal = Vector3(0.0f, 0.0f, 1.0f);

	intersection.HitObject = (Model*)&box;
	return true;
}

bool RayAndVoxelModel(const Ray &ray, const Vector3 &vmin, const Vector3 &vmax, float &param)
{
	static const float EPSILON = FLT_EPSILON;

	float t[8] = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f };

	if (Math::Abs(ray.Direction.x) > EPSILON)
	{
		t[0] = (vmin.x - ray.Position.x) / ray.Direction.x;
		t[1] = (vmax.x - ray.Position.x) / ray.Direction.x;
	}

	if (Math::Abs(ray.Direction.y) > EPSILON)
	{
		t[2] = (vmin.y - ray.Position.y) / ray.Direction.y;
		t[3] = (vmax.y - ray.Position.y) / ray.Direction.y;
	}

	if (Math::Abs(ray.Direction.z) > EPSILON)
	{
		t[4] = (vmin.z - ray.Position.z) / ray.Direction.z;
		t[5] = (vmax.z - ray.Position.z) / ray.Direction.z;
	}

	t[6] = Math::Max(Math::Min(t[0], t[1]), Math::Min(t[2], t[3]), Math::Min(t[4], t[5]));
	t[7] = Math::Min(Math::Max(t[0], t[1]), Math::Max(t[2], t[3]), Math::Max(t[4], t[5]));

	if (t[7] < 0.0f || t[6] > t[7] || t[6] > ray.MaxDistance)
		return false;

	param = t[6];
	return true;
}

inline bool IsPointInVoxelModel(const Vector3 &point, const Vector3 &min, const Vector3 &max)
{
	if (point.x > min.x && point.x < max.x
		&& point.y > min.y && point.y < max.y
		&& point.z > min.z && point.z < max.z)
		return true;

	return false;
}

inline void GetNormal(const Vector3 &point, const Vector3 &vmin, const Vector3 &vmax, Vector3 &normal)
{
	static const float EPSILON = 0.0001f;

	if (Math::Abs(point.x - vmin.x) < EPSILON)
	{
		normal = Vector3(-1.0f, 0.0f, 0.0f);
		return;
	}
	if (Math::Abs(point.x - vmax.x) < EPSILON)
	{
		normal = Vector3(1.0f, 0.0f, 0.0f);
		return;
	}

	if (Math::Abs(point.y - vmin.y) < EPSILON)
	{
		normal = Vector3(0.0f, -1.0f, 0.0f);
		return;
	}
	if (Math::Abs(point.y - vmax.y) < EPSILON)
	{
		normal = Vector3(0.0f, 1.0f, 0.0f);
		return;
	}

	if (Math::Abs(point.z - vmin.z) < EPSILON)
	{
		normal = Vector3(0.0f, 0.0f, -1.0f);
		return;
	}
	if (Math::Abs(point.z - vmax.z) < EPSILON)
	{
		normal = Vector3(0.0f, 0.0f, 1.0f);
		return;
	}
}

/*
Thanks to:
John Amanatides and Andrew Woo, A Fast Voxel Traversal Algorithm for Ray Tracing (In Eurographics ’87)
*/

bool RayAndVoxelGrid(const Ray &ray, const VoxelModel &box, RayHit &intersection)
{
	Vector3 relStartPosition;
	if (IsPointInVoxelModel(ray.Position, box.Position, box.GetSizePoint() + box.Position))
	{
		relStartPosition = (ray.Position - box.Position);
		GetNormal(relStartPosition, box.Position, box.GetSizePoint(), intersection.Normal);
	}
	else
	{
		float param;
		if (!RayAndVoxelModel(ray, box.Position, box.GetSizePoint(), param))
			return false; // ray doesn't hit voxel model volume

		Vector3 voxelModelIntersection = ray.Position + param * ray.Direction;
		GetNormal(voxelModelIntersection, box.Position, box.GetSizePoint(), intersection.Normal);
		voxelModelIntersection += (0.0001f * ray.Direction); // move a bit into voxel model volume
		relStartPosition = (voxelModelIntersection - box.Position);
	}

	int index[3] = {
		(int)Math::Floor(relStartPosition.x / VoxelModel::VOXEL_SIZE_X),
		(int)Math::Floor(relStartPosition.y / VoxelModel::VOXEL_SIZE_Y),
		(int)Math::Floor(relStartPosition.z / VoxelModel::VOXEL_SIZE_Z)
	};
	intersection.Position = relStartPosition + box.Position;
	intersection.HitObject = (Model*)&box;

	int size[3] = {
		(int)box.GetSizeX(),
		(int)box.GetSizeY(),
		(int)box.GetSizeZ()
	};

	if (index[0] >= size[0] || index[0] < 0)
		return false;
	if (index[1] >= size[1] || index[1] < 0)
		return false;
	if (index[2] >= size[2] || index[2] < 0)
		return false;

	int step[3];
	float tMax[3];

	if (ray.Direction.x >= 0.0f)
	{
		step[0] = 1;
		tMax[0] = (VoxelModel::VOXEL_SIZE_X - Math::Mod(relStartPosition.x, VoxelModel::VOXEL_SIZE_X)) / ray.Direction.x;
	}
	else
	{
		step[0] = -1;
		tMax[0] = (0.0f - Math::Mod(relStartPosition.x, VoxelModel::VOXEL_SIZE_X)) / ray.Direction.x;
	}

	if (ray.Direction.y >= 0.0f)
	{
		step[1] = 1;
		tMax[1] = (VoxelModel::VOXEL_SIZE_Y - Math::Mod(relStartPosition.y, VoxelModel::VOXEL_SIZE_Y)) / ray.Direction.y;
	}
	else
	{
		step[1] = -1;
		tMax[1] = (0.0f - Math::Mod(relStartPosition.y, VoxelModel::VOXEL_SIZE_Y)) / ray.Direction.y;
	}

	if (ray.Direction.z >= 0.0f)
	{
		step[2] = 1;
		tMax[2] = (VoxelModel::VOXEL_SIZE_Z - Math::Mod(relStartPosition.z, VoxelModel::VOXEL_SIZE_Z)) / ray.Direction.z;
	}
	else
	{
		step[2] = -1;
		tMax[2] = (0.0f - Math::Mod(relStartPosition.z, VoxelModel::VOXEL_SIZE_Z)) / ray.Direction.z;
	}

	float tDelta[3] = {
		Math::Abs(VoxelModel::VOXEL_SIZE_X / ray.Direction.x),
		Math::Abs(VoxelModel::VOXEL_SIZE_Y / ray.Direction.y),
		Math::Abs(VoxelModel::VOXEL_SIZE_Z / ray.Direction.z)
	};

	float lastT = 0.0f;

	for (;;)
	{
		if (box.GetVoxel(index[0], index[1], index[2]) != 0)
		{
			intersection.HitObject = (Model*)&box;
			intersection.Position = relStartPosition + lastT * ray.Direction + box.Position;
			break;
		}

		if (tMax[0] < tMax[1])
		{
			if (tMax[0] < tMax[2])
			{
				index[0] += step[0];
				if (index[0] >= size[0] || index[0] < 0)
					return false; // outside grid
				lastT = tMax[0];
				tMax[0] += tDelta[0];
				intersection.Normal = Vector3((float)-step[0], 0.0f, 0.0f);
			}
			else
			{
				index[2] += step[2];
				if (index[2] >= size[2] || index[2] < 0)
					return false; // outside grid
				lastT = tMax[2];
				tMax[2] += tDelta[2];
				intersection.Normal = Vector3(0.0f, 0.0f, (float)-step[2]);
			}
		}
		else
		{
			if (tMax[1] < tMax[2])
			{
				index[1] += step[1];
				if (index[1] >= size[1] || index[1] < 0)
					return false; // outside grid
				lastT = tMax[1];
				tMax[1] += tDelta[1];
				intersection.Normal = Vector3(0.0f, (float)-step[1], 0.0f);
			}
			else
			{
				index[2] += step[2];
				if (index[2] >= size[2] || index[2] < 0)
					return false; // outside grid
				lastT = tMax[2];
				tMax[2] += tDelta[2];
				intersection.Normal = Vector3(0.0f, 0.0f, (float)-step[2]);
			}
		}

		if (lastT > ray.MaxDistance)
			return false;
	}

	return true;
}

} // ~ namespace Intersections

} // ~ namespace LumixRayTracer
