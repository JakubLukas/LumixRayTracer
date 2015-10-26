#include "collisions.h"

#include "ray.h"
#include "primitives/sphere.h"
#include "math_rt.h"


namespace LumixRayTracer
{

namespace Collisions
{

bool Collisions::RayAndSphere(const Ray &ray, const Sphere &sphere, RayHit &intersection)
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
			intersection = ray.Position;
		}
		else // occurs when p is inside the sphere
		{
			Vector3 pc = ray.Position + ray.Direction * Vector3::Dot(ray.Direction, vpc) / ray.Direction.length();//projection of c on the line
				// distance from pc to i1
			float dist = Math::Sqrt(sphere.Radius*sphere.Radius - (pc - sphere.Position).length()*(pc - sphere.Position).length());
			float di1 = dist - (pc - ray.Position).length();
			intersection = ray.Position + ray.Direction * di1;
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
			float di1;
			if (vpc.length() > sphere.Radius) // origin is outside sphere	
			{
				di1 = (pc - ray.Position).length() - dist;
			}
			else // origin is inside sphere
			{
				di1 = (pc - ray.Position).length() + dist;
			}
			intersection = ray.Position + ray.Direction * di1;
		}
	}

	return true;
}

} // ~ namespace Collisions

} // ~ namespace LumixRayTracer
