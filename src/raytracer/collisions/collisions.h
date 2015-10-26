#pragma once


namespace LumixRayTracer
{
struct Vector3;
struct Ray;
struct Sphere;
struct RayHit;

namespace Collisions
{

bool RayAndSphere(const Ray &ray, const Sphere &sphere, RayHit &intersection);

} // ~ namespace Collisions

} // ~ namespace LumixRayTracer
