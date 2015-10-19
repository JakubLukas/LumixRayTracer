#include "collisions.h"

#include "ray.h"
#include "sphere.h"


namespace LumixRayTracer
{

namespace Collisions
{

Vector3 Collisions::RayAndSphere(Ray ray, Sphere sphere)
{
	Vector3 intersection;
	Vector3 vpc = sphere.Position - ray.Position;

	if (Vector3.Dot(vpc, ray.Direction) < 0.0f) // when the sphere is behind the origin p
		// note that this case may be dismissed if it is 
		// considered that p is outside the sphere 	
		if (vpc.length() > sphere.Radius)
			;// there is no intersection
		else if (vpc.length() == sphere.Radius)
			intersection = ray.Position;
		else // occurs when p is inside the sphere
			pc = projection of c on the line
			// distance from pc to i1
			dist = sqrt(radius ^ 2 - | pc - c | ^ 2)
			di1 = dist - | pc - p |
			intersection = p + d * di1

		else // center of sphere projects on the ray

		pc = projection of c on the line
		if (| c - pc | > r)

			// there is no intersection

		else
		// distance from pc to i1
		dist = sqrt(radius ^ 2 - | pc - c | ^ 2)

		if (| vpc | > r) // origin is outside sphere	

			di1 = | pc - p | -dist

		else // origin is inside sphere

		di1 = | pc - p | +dist

		intersection = p + d * di1

	return Vector3();
}

} // ~ namespace Collisions

} // ~ namespace LumixRayTracer
