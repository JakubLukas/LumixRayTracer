#pragma once

#include <cstdint>
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
	inline void SetVoxel(const uint32_t x, const uint32_t y, const uint32_t z, const uint8_t value);
public:
	inline uint8_t GetVoxel(const uint32_t x, const uint32_t y, const uint32_t z) const;

	inline uint32_t GetSizeX() const { return _sizeX; };
	inline uint32_t GetSizeY() const { return _sizeY; };
	inline uint32_t GetSizeZ() const { return _sizeZ; };
	inline const Vector3 &GetSizePoint() const { return _maxPoint; };

};

inline void VoxelModel::SetVoxel(const uint32_t x, const uint32_t y, const uint32_t z, const uint8_t value)
{
	ASSERT(x < _sizeX && y < _sizeY && z < _sizeZ);
	_data[x * _sizeX * _sizeY + y * _sizeY + z] = value;
}

inline uint8_t VoxelModel::GetVoxel(const uint32_t x, const uint32_t y, const uint32_t z) const
{
	ASSERT(x < _sizeX && y < _sizeY && z < _sizeZ);
	return _data[x * _sizeX * _sizeY + y * _sizeY + z];
}

} // ~ namespace LumixRayTracer
