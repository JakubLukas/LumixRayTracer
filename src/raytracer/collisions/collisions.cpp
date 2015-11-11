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
	static const float EPSILON = FLT_EPSILON;

	const Vector3 boxMax = model.GetMaxPoint();

	float t1(-1.0f);
	float t2(-1.0f);
	float t3(-1.0f);
	float t4(-1.0f);
	float t5(-1.0f);
	float t6(-1.0f);

	if (ray.Direction.x > EPSILON || ray.Direction.x < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.x;
		t1 = (model.Position.x - ray.Position.x) * dirfrac;
		t2 = (boxMax.x - ray.Position.x) * dirfrac;
	}

	if (ray.Direction.y > EPSILON || ray.Direction.y < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.y;
		t3 = (model.Position.y - ray.Position.y) * dirfrac;
		t4 = (boxMax.y - ray.Position.y) * dirfrac;
	}

	if (ray.Direction.z > EPSILON || ray.Direction.z < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.z;
		t5 = (model.Position.z - ray.Position.z) * dirfrac;
		t6 = (boxMax.z - ray.Position.z) * dirfrac;
	}

	float tmin = Math::Max(Math::Min(t1, t2), Math::Min(t3, t4), Math::Min(t5, t6));
	float tmax = Math::Min(Math::Max(t1, t2), Math::Max(t3, t4), Math::Max(t5, t6));

	if (tmax < 0.0f) // if tmax < 0, ray is intersecting AABB, but whole AABB is behing us
		return false;

	if (tmin > tmax) // if tmin > tmax, ray doesn't intersect AABB
		return false;

	intersection = tmin;
	return true;
}

/*
Thanks to:
John Amanatides and Andrew Woo, A Fast Voxel Traversal Algorithm for Ray Tracing (In Eurographics ’87)
*/

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

	int X = (int)Math::Floor(relVoxIntersect.x / VoxelModel::VOXEL_SIZE_X);
	int Y = (int)Math::Floor(relVoxIntersect.y / VoxelModel::VOXEL_SIZE_Y);
	int Z = (int)Math::Floor(relVoxIntersect.z / VoxelModel::VOXEL_SIZE_Z);
	int sizeX = (int)box.GetSizeX();
	int sizeY = (int)box.GetSizeY();
	int sizeZ = (int)box.GetSizeZ();

	if (X >= sizeX || X < 0)
		return false;
	if (Y >= sizeY || Y < 0)
		return false;
	if (Z >= sizeZ || Z < 0)
		return false;

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
			intersection.Position = Vector3(X, Y, Z);
			intersection.Normal = Vector3();
			return true;
		}

		if (tMaxX < tMaxY)
		{
			if (tMaxX < tMaxZ)
			{
				X = X + stepX;
				if (X >= sizeX || X < 0)
					return false; // outside grid
				tMaxX = tMaxX + tDeltaX;
				intersection.Normal.x = stepX;
				intersection.Normal.y = 0.0f;
				intersection.Normal.z = 0.0f;
			}
			else
			{
				Z = Z + stepZ;
				if (Z >= sizeZ || Z < 0)
					return false; // outside grid
				tMaxZ = tMaxZ + tDeltaZ;
				intersection.Normal.x = 0.0f;
				intersection.Normal.y = 0.0f;
				intersection.Normal.z = stepZ;
			}
		}
		else
		{
			if (tMaxY < tMaxZ)
			{
				Y = Y + stepY;
				if (Y >= sizeY || Y < 0)
					return false; // outside grid
				tMaxY = tMaxY + tDeltaY;
				intersection.Normal.x = 0.0f;
				intersection.Normal.y = stepY;
				intersection.Normal.z = 0.0f;
			}
			else
			{
				Z = Z + stepZ;
				if (Z >= sizeZ || Z < 0)
					return false; // outside grid
				tMaxZ = tMaxZ + tDeltaZ;
				intersection.Normal.x = 0.0f;
				intersection.Normal.y = 0.0f;
				intersection.Normal.z = stepZ;
			}
		}
	}

	return false;
}

} // ~ namespace Intersections

} // ~ namespace LumixRayTracer
