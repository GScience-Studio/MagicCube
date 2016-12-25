#pragma once

#include "ChunkManager.h"

class world :public chunk_manager
{
public:
	world() :chunk_manager(this)
	{

	}
	void buildChunk(chunk* chunk)
	{
		if (chunk->getChunkY() == 0)
		{
			for (uint8_t i = 0; i < 16; i++)
				for (uint8_t j = 0; j < 16; j++)
					chunk->getBlock(i, 0, j)->setBlockID(1);

			for (uint8_t i = 0; i < 16; i++)
				for (uint8_t j = 0; j < 16; j++)
					chunk->getBlock(i, 2, j)->setBlockID(32);
		}
		chunk->_isNewChunk.store(false);
	}
};