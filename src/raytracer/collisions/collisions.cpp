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

	if (tmax < 0.0f) // box is behind
		return false;

	if (tmin > tmax) // ray doesn't intersect box
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

	const Vector3 boxMax = model.GetSizePoint();

	float t[6] = { -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f };

	if (ray.Direction.x > EPSILON || ray.Direction.x < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.x;
		t[0] = (model.Position.x - ray.Position.x) * dirfrac;
		t[1] = (boxMax.x - ray.Position.x) * dirfrac;
	}

	if (ray.Direction.y > EPSILON || ray.Direction.y < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.y;
		t[2] = (model.Position.y - ray.Position.y) * dirfrac;
		t[3] = (boxMax.y - ray.Position.y) * dirfrac;
	}

	if (ray.Direction.z > EPSILON || ray.Direction.z < -EPSILON)
	{
		float dirfrac = 1.0f / ray.Direction.z;
		t[4] = (model.Position.z - ray.Position.z) * dirfrac;
		t[5] = (boxMax.z - ray.Position.z) * dirfrac;
	}

	float tmin = Math::Max(Math::Min(t[0], t[1]), Math::Min(t[2], t[3]), Math::Min(t[4], t[5]));
	float tmax = Math::Min(Math::Max(t[0], t[1]), Math::Max(t[2], t[3]), Math::Max(t[4], t[5]));

	if (tmax < 0.0f) // box is behind
		return false;

	if (tmin > tmax) // ray doesn't intersect box
		return false;

	intersection = tmin;
	return true;
}

bool IsPointInVoxelModel(const Vector3 &point, const Vector3 &min, const Vector3 &max)
{
	if (point.x > min.x && point.x < max.x
			&& point.y > min.y && point.y < max.y
			&& point.z > min.z && point.z < max.z)
			return true;

	return false;
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
	}
	else
	{
		float param;
		if (!RayAndVoxelModel(ray, box, param))
			return false; // ray doesn't hit voxel model volume

		param += 0.0001f; // move a bit into voxel model volume
		Vector3 voxelModelIntersection = ray.Position + param * ray.Direction;
		relStartPosition = (voxelModelIntersection - box.Position);
	}

	int X = (int)Math::Floor(relStartPosition.x / VoxelModel::VOXEL_SIZE_X);
	int Y = (int)Math::Floor(relStartPosition.y / VoxelModel::VOXEL_SIZE_Y);
	int Z = (int)Math::Floor(relStartPosition.z / VoxelModel::VOXEL_SIZE_Z);
	intersection.Position = Vector3(X, Y, Z);

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

	float modX = Math::Mod(relStartPosition.x, VoxelModel::VOXEL_SIZE_X);
	float modY = Math::Mod(relStartPosition.y, VoxelModel::VOXEL_SIZE_Y);
	float modZ = Math::Mod(relStartPosition.z, VoxelModel::VOXEL_SIZE_Z);

	float tMaxX = (ray.Direction.x > 0.0f) ? VoxelModel::VOXEL_SIZE_X : 0.0f;
	tMaxX = (tMaxX - Math::Mod(relStartPosition.x, VoxelModel::VOXEL_SIZE_X)) / ray.Direction.x;
	float tMaxY = (ray.Direction.y > 0.0f) ? VoxelModel::VOXEL_SIZE_Y : 0.0f;
	tMaxY = (tMaxY - Math::Mod(relStartPosition.y, VoxelModel::VOXEL_SIZE_Y)) / ray.Direction.y;
	float tMaxZ = (ray.Direction.z > 0.0f) ? VoxelModel::VOXEL_SIZE_Z : 0.0f;
	tMaxZ = (tMaxZ - Math::Mod(relStartPosition.z, VoxelModel::VOXEL_SIZE_Z)) / ray.Direction.z;

	float tDeltaX = Math::Abs(VoxelModel::VOXEL_SIZE_X / ray.Direction.x);
	float tDeltaY = Math::Abs(VoxelModel::VOXEL_SIZE_Y / ray.Direction.y);
	float tDeltaZ = Math::Abs(VoxelModel::VOXEL_SIZE_Z / ray.Direction.z);

	float tLast = 0.0f;

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
				tLast = tMaxX;
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
				tLast = tMaxZ;
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
				tLast = tMaxY;
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
				tLast = tMaxZ;
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
