#include "voxel_model.h"


namespace LumixRayTracer
{

VoxelModel::VoxelModel(const uint32_t sizeX, const uint32_t sizeY, const uint32_t sizeZ)
	: Model(), _sizeX(sizeX), _sizeY(sizeY), _sizeZ(sizeZ)
{
	_data = (uint8_t*)calloc(sizeX * sizeY * sizeZ, sizeof(uint8_t));

	SetVoxel(0, 0, 0, 1);
}


void VoxelModel::SetVoxel(const uint32_t x, const uint32_t y, const uint32_t z, const uint8_t value)
{
	_data[x * _sizeX * _sizeY + y * _sizeY + z] = value;
}

uint8_t VoxelModel::GetVoxel(const uint32_t x, const uint32_t y, const uint32_t z) const
{
	return _data[x * _sizeX * _sizeY + y * _sizeY + z];
}

} // ~ namespace LumixRayTracer
