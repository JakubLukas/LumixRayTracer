#pragma once


namespace LumixRayTracer
{
struct Vector3;
struct Ray;
struct Sphere;

namespace Collisions
{

Vector3 RayAndSphere(Ray ray, Sphere sphere);

} // ~ namespace Collisions

} // ~ namespace LumixRayTracer
