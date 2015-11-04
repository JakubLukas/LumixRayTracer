#include "collisions.h"

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

bool Intersections::RayAndSphere(const Ray &ray, const Sphere &sphere, RayHit &intersection)
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

			intersection.Position = ray.Position + ray.Direction * di1;
		}
	}
	intersection.Normal = intersection.Position - sphere.Position;
	intersection.Normal.normalize();
	intersection.HitObject = (Model*)&sphere;

	return true;
}

bool Intersections::RayAndBox(const Ray &ray, const Box &box, RayHit &intersection)
{
	// r.dir is unit direction vector of ray
	Vector3 dirfrac(1.0f / ray.Direction.x, 1.0f / ray.Direction.y, 1.0f / ray.Direction.z);

	Vector3 boxMax = box.Position + box.Size;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (box.Position.x - ray.Position.x) * dirfrac.x;
	float t2 = (boxMax.x - ray.Position.x) * dirfrac.x;
	float t3 = (box.Position.y - ray.Position.y) * dirfrac.y;
	float t4 = (boxMax.y - ray.Position.y) * dirfrac.y;
	float t5 = (box.Position.z - ray.Position.z) * dirfrac.z;
	float t6 = (boxMax.z - ray.Position.z) * dirfrac.z;

	float tmin = Math::Max(Math::Max(Math::Min(t1, t2), Math::Min(t3, t4)), Math::Min(t5, t6));
	float tmax = Math::Min(Math::Min(Math::Max(t1, t2), Math::Max(t3, t4)), Math::Max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	intersection.Position = box.Position + ray.Direction * tmin;

	if (tmin == t1)
		intersection.Normal = Vector3(1.0f, 0.0f, 0.0f);
	if (tmin == t2)
		intersection.Normal = Vector3(-1.0f, 0.0f, 0.0f);
	if (tmin == t3)
		intersection.Normal = Vector3(0.0f, 1.0f, 0.0f);
	if (tmin == t4)
		intersection.Normal = Vector3(0.0f, -1.0f, 0.0f);
	if (tmin == t5)
		intersection.Normal = Vector3(0.0f, 0.0f, 1.0f);
	if (tmin == t6)
		intersection.Normal = Vector3(0.0f, 0.0f, -1.0f);

	intersection.HitObject = (Model*)&box;
	return true;
}

bool RayAndVoxelModel(const Ray &ray, const VoxelModel &model, Vector3 &intersection)
{
	// r.dir is unit direction vector of ray
	Vector3 dirfrac(1.0f / ray.Direction.x, 1.0f / ray.Direction.y, 1.0f / ray.Direction.z);

	const Vector3 boxMax = model.GetMaxPoint();
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (model.Position.x - ray.Position.x) * dirfrac.x;
	float t2 = (boxMax.x - ray.Position.x) * dirfrac.x;
	float t3 = (model.Position.y - ray.Position.y) * dirfrac.y;
	float t4 = (boxMax.y - ray.Position.y) * dirfrac.y;
	float t5 = (model.Position.z - ray.Position.z) * dirfrac.z;
	float t6 = (boxMax.z - ray.Position.z) * dirfrac.z;

	float tmin = Math::Max(Math::Max(Math::Min(t1, t2), Math::Min(t3, t4)), Math::Min(t5, t6));
	float tmax = Math::Min(Math::Min(Math::Max(t1, t2), Math::Max(t3, t4)), Math::Max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	intersection = model.Position + ray.Direction * tmin;
	return true;
}

bool RayAndVoxelGrid(const Ray &ray, const VoxelModel &box, bool(*func_pointer)(uint8_t))
{
	Vector3 voxelModelIntersection;
	if (!RayAndVoxelModel(ray, box, voxelModelIntersection))
		return false;

	Vector3 relVoxIntersect = (voxelModelIntersection - box.Position);
	int X = int(relVoxIntersect.x / VoxelModel::VOXEL_SIZE_X);
	int Y = int(relVoxIntersect.y / VoxelModel::VOXEL_SIZE_Y);
	int Z = int(relVoxIntersect.z / VoxelModel::VOXEL_SIZE_Z);

	int stepX = (ray.Direction.x <= 0.0f) ? 1 : -1;
	int stepY = (ray.Direction.y <= 0.0f) ? 1 : -1;
	int stepZ = (ray.Direction.z <= 0.0f) ? 1 : -1;

	float tMaxX = (box.Position.x - ray.Position.x) / ray.Direction.x;
	float tMaxY = (box.Position.y - ray.Position.y) / ray.Direction.y;
	float tMaxZ = (box.Position.z - ray.Position.z) / ray.Direction.z;

	for (;;)
	{
		if (tMaxX < tMaxY)
		{
			if (tMaxX < tMaxZ)
			{
				X = X + stepX;
				if (X >= box.GetSizeX())
					return false; // outside grid
				tMaxX = tMaxX + VoxelModel::VOXEL_SIZE_X;
			}
			else
			{
				Z = Z + stepZ;
				if (Z == box.GetSizeZ())
					return false; // outside grid
				tMaxZ = tMaxZ + VoxelModel::VOXEL_SIZE_Z;
			}
		}
		else
		{
			if (tMaxY < tMaxZ)
			{
				Y = Y + stepY;
				if (Y == box.GetSizeY())
					return false; // outside grid
				tMaxY = tMaxY + VoxelModel::VOXEL_SIZE_Y;
			}
			else
			{
				Z = Z + stepZ;
				if (Z == box.GetSizeZ())
					return false; // outside grid
				tMaxZ = tMaxZ + VoxelModel::VOXEL_SIZE_Z;
			}
		}
		if (func_pointer(box.GetVoxel(X, Y, Z)))
			return true;
	}
}

} // ~ namespace Intersections

} // ~ namespace LumixRayTracer
