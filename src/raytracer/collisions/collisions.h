#pragma once

#include <functional>


namespace LumixRayTracer
{
struct Vector3;
struct Ray;
struct Sphere;
struct Box;
class VoxelModel;
struct RayHit;

namespace Intersections
{

bool RayAndSphere(const Ray &ray, const Sphere &sphere, RayHit &intersection);
bool RayAndBox(const Ray &ray, const Box &box, RayHit &intersection);
bool RayAndVoxelModel(const Ray &ray, const VoxelModel &model, Vector3 &intersection);
bool RayAndVoxelGrid(const Ray &ray, const VoxelModel &box, RayHit &intersection);

} // ~ namespace Intersections

} // ~ namespace LumixRayTracer
