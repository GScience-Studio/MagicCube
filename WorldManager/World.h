#pragma once

#include "ChunkManager.h"

class world :public chunk_manager
{
public:
	world() :chunk_manager(this)
	{

	}
};