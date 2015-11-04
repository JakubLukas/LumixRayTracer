#pragma once

#include "model.h"


namespace LumixRayTracer
{

class VoxelModel : public Model
{
public:
	static const float VOXEL_SIZE_X;
	static const float VOXEL_SIZE_Y;
	static const float VOXEL_SIZE_Z;

private:
	uint32_t _sizeX;
	uint32_t _sizeY;
	uint32_t _sizeZ;
	uint8_t* _data;
	Vector3 _maxPoint;

public:
	VoxelModel(const uint32_t sizeX, const uint32_t sizeY, const uint32_t sizeZ);

private:
	void SetVoxel(const uint32_t x, const uint32_t y, const uint32_t z, const uint8_t value);
public:
	uint8_t GetVoxel(const uint32_t x, const uint32_t y, const uint32_t z) const;

	inline uint32_t GetSizeX() const { return _sizeX; };
	inline uint32_t GetSizeY() const { return _sizeY; };
	inline uint32_t GetSizeZ() const { return _sizeZ; };
	inline const Vector3 &GetMaxPoint() const;

};

const float VoxelModel::VOXEL_SIZE_X = 1.0f;
const float VoxelModel::VOXEL_SIZE_Y = 1.0f;
const float VoxelModel::VOXEL_SIZE_Z = 1.0f;

} // ~ namespace LumixRayTracer
