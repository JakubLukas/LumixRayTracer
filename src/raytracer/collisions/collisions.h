#pragma once


namespace LumixRayTracer
{
struct Vector3;
struct Ray;
struct Sphere;

namespace Collisions
{

bool RayAndSphere(const Ray &ray, const Sphere &sphere, Vector3 &intersection);

} // ~ namespace Collisions

} // ~ namespace LumixRayTracer
