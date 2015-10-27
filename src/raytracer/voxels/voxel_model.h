#pragma once

#include "model.h"


namespace LumixRayTracer
{

class VoxelModel : public Model
{
private:
	uint8_t*** _data;

public:
	VoxelModel()
		: Model()
	{}


};

} // ~ namespace LumixRayTracer
