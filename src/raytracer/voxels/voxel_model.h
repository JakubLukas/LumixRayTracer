#pragma once

#include "model.h"


namespace LumixRayTracer
{

class VoxelModel : public Model
{


private:
	uint32_t _sizeX;
	uint32_t _sizeY;
	uint32_t _sizeZ;
	uint8_t* _data;

public:
	VoxelModel(const uint32_t sizeX, const uint32_t sizeY, const uint32_t sizeZ);

private:
	void SetVoxel(const uint32_t x, const uint32_t y, const uint32_t z, const uint8_t value);
	uint8_t GetVoxel(const uint32_t x, const uint32_t y, const uint32_t z) const;

};

} // ~ namespace LumixRayTracer
