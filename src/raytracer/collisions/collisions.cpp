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
	Vector3 dirfrac(
		(ray.Direction.x < 0.0001f && ray.Direction.x > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.x,
		(ray.Direction.y < 0.0001f && ray.Direction.y > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.y,
		(ray.Direction.z < 0.0001f && ray.Direction.z > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.z
		);

	Vector3 boxMax = box.Position + box.Size;
	float t1 = (box.Position.x - ray.Position.x) * dirfrac.x;
	float t2 = (boxMax.x - ray.Position.x) * dirfrac.x;
	float t3 = (box.Position.y - ray.Position.y) * dirfrac.y;
	float t4 = (boxMax.y - ray.Position.y) * dirfrac.y;
	float t5 = (box.Position.z - ray.Position.z) * dirfrac.z;
	float t6 = (boxMax.z - ray.Position.z) * dirfrac.z;

	float tmin = Math::Max(Math::Min(t1, t2), Math::Min(t3, t4), Math::Min(t5, t6));
	float tmax = Math::Min(Math::Max(t1, t2), Math::Max(t3, t4), Math::Max(t5, t6));

	if (tmax < 0) // if tmax < 0, ray is intersecting AABB, but whole AABB is behing us
		return false;

	if (tmin > tmax) // if tmin > tmax, ray doesn't intersect AABB
		return false;

	intersection.Position = ray.Position + ray.Direction * tmin;

	if (Math::Abs(intersection.Position.x - box.Position.x) < 0.0001f)
		intersection.Normal = Vector3(-1.0f, 0.0f, 0.0f);
	else if (Math::Abs(intersection.Position.x - boxMax.x) < 0.0001f)
		intersection.Normal = Vector3(1.0f, 0.0f, 0.0f);
	else if (Math::Abs(intersection.Position.y - box.Position.y) < 0.0001f)
		intersection.Normal = Vector3(0.0f, -1.0f, 0.0f);
	else if (Math::Abs(intersection.Position.y - boxMax.y) < 0.0001f)
		intersection.Normal = Vector3(0.0f, 1.0f, 0.0f);
	else if (Math::Abs(intersection.Position.z - box.Position.z) < 0.0001f)
		intersection.Normal = Vector3(0.0f, 0.0f, -1.0f);
	else if (Math::Abs(intersection.Position.z - boxMax.z) < 0.0001f)
		intersection.Normal = Vector3(0.0f, 0.0f, 1.0f);

	intersection.HitObject = (Model*)&box;
	return true;
}

bool RayAndVoxelModel(const Ray &ray, const VoxelModel &model, float &intersection)
{
	Vector3 dirfrac(
		(ray.Direction.x < 0.0001f && ray.Direction.x > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.x,
		(ray.Direction.y < 0.0001f && ray.Direction.y > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.y,
		(ray.Direction.z < 0.0001f && ray.Direction.z > -0.0001f) ? 0.0001f : 1.0f / ray.Direction.z
		);

	const Vector3 boxMax = model.GetMaxPoint();
	float t1 = (model.Position.x - ray.Position.x) * dirfrac.x;
	float t2 = (boxMax.x - ray.Position.x) * dirfrac.x;
	float t3 = (model.Position.y - ray.Position.y) * dirfrac.y;
	float t4 = (boxMax.y - ray.Position.y) * dirfrac.y;
	float t5 = (model.Position.z - ray.Position.z) * dirfrac.z;
	float t6 = (boxMax.z - ray.Position.z) * dirfrac.z;

	float tmin = Math::Max(Math::Min(t1, t2), Math::Min(t3, t4), Math::Min(t5, t6));
	float tmax = Math::Min(Math::Max(t1, t2), Math::Max(t3, t4), Math::Max(t5, t6));

	if (tmax < 0) // if tmax < 0, ray is intersecting AABB, but whole AABB is behing us
		return false;

	if (tmin > tmax) // if tmin > tmax, ray doesn't intersect AABB
		return false;

	intersection = tmin;
	return true;
}

bool RayAndVoxelGrid(const Ray &ray, const VoxelModel &box, RayHit &intersection)
{
	float param;
	if (!RayAndVoxelModel(ray, box, param))
		return false;

	param += 0.0001f;
	Vector3 voxelModelIntersection = ray.Position + param * ray.Direction;

	Vector3 relVoxIntersect;
	if (ray.Position.x >= box.Position.x
			&& ray.Position.y >= box.Position.y
			&& ray.Position.z >= box.Position.z
			&& ray.Position.x <= box.GetMaxPoint().x
			&& ray.Position.y <= box.GetMaxPoint().y
			&& ray.Position.z <= box.GetMaxPoint().z)
		relVoxIntersect = (ray.Position - box.Position);
	else
		relVoxIntersect = (voxelModelIntersection - box.Position);

	int X = relVoxIntersect.x / VoxelModel::VOXEL_SIZE_X;
	int Y = relVoxIntersect.y / VoxelModel::VOXEL_SIZE_Y;
	int Z = relVoxIntersect.z / VoxelModel::VOXEL_SIZE_Z;

	if (X >= box.GetSizeX())
		X = box.GetSizeX()-1;
	if (X < 0)
		X = 0;
	if (Y >= box.GetSizeY())
		Y = box.GetSizeY()-1;
	if (Y < 0)
		Y = 0;
	if (Z >= box.GetSizeZ())
		Z = box.GetSizeZ()-1;
	if (Z < 0)
		Z = 0;

	int stepX = (ray.Direction.x >= 0.0f) ? 1 : -1;
	int stepY = (ray.Direction.y >= 0.0f) ? 1 : -1;
	int stepZ = (ray.Direction.z >= 0.0f) ? 1 : -1;

	float modX = Math::Mod(relVoxIntersect.x, VoxelModel::VOXEL_SIZE_X);
	float modY = Math::Mod(relVoxIntersect.y, VoxelModel::VOXEL_SIZE_Y);
	float modZ = Math::Mod(relVoxIntersect.z, VoxelModel::VOXEL_SIZE_Z);

	float tMaxX = (ray.Direction.x > 0.0f) ? VoxelModel::VOXEL_SIZE_X : 0.0f;
	tMaxX = (tMaxX - Math::Mod(relVoxIntersect.x, VoxelModel::VOXEL_SIZE_X)) / ray.Direction.x;
	float tMaxY = (ray.Direction.y > 0.0f) ? VoxelModel::VOXEL_SIZE_Y : 0.0f;
	tMaxY = (tMaxY - Math::Mod(relVoxIntersect.y, VoxelModel::VOXEL_SIZE_Y)) / ray.Direction.y;
	float tMaxZ = (ray.Direction.z > 0.0f) ? VoxelModel::VOXEL_SIZE_Z : 0.0f;
	tMaxZ = (tMaxZ - Math::Mod(relVoxIntersect.z, VoxelModel::VOXEL_SIZE_Z)) / ray.Direction.z;

	float tDeltaX = Math::Abs(VoxelModel::VOXEL_SIZE_X / ray.Direction.x);
	float tDeltaY = Math::Abs(VoxelModel::VOXEL_SIZE_Y / ray.Direction.y);
	float tDeltaZ = Math::Abs(VoxelModel::VOXEL_SIZE_Z / ray.Direction.z);

	intersection.Position = Vector3(X, Y, Z);
	for (;;)
	{
		if (box.GetVoxel(X, Y, Z) != 0)
		{
			intersection.HitObject = (Model*)&box;
			intersection.Normal = Vector3();
			return true;
		}

		if (tMaxX < tMaxY)
		{
			if (tMaxX < tMaxZ)
			{
				X = X + stepX;
				if (X >= box.GetSizeX() || X < 0)
					return false; // outside grid
				intersection.Position = Vector3(X, Y, Z);
				tMaxX = tMaxX + tDeltaX;
			}
			else
			{
				Z = Z + stepZ;
				if (Z >= box.GetSizeZ() || Z < 0)
					return false; // outside grid
				intersection.Position = Vector3(X, Y, Z);
				tMaxZ = tMaxZ + tDeltaZ;
			}
		}
		else
		{
			if (tMaxY < tMaxZ)
			{
				Y = Y + stepY;
				if (Y >= box.GetSizeY() || Y < 0)
					return false; // outside grid
				intersection.Position = Vector3(X, Y, Z);
				tMaxY = tMaxY + tDeltaY;
			}
			else
			{
				Z = Z + stepZ;
				if (Z >= box.GetSizeZ() || Z < 0)
					return false; // outside grid
				intersection.Position = Vector3(X, Y, Z);
				tMaxZ = tMaxZ + tDeltaZ;
			}
		}
	}

	return false;
}

} // ~ namespace Intersections

} // ~ namespace LumixRayTracer
