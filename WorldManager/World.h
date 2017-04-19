#pragma once

#include "ChunkManager.h"

float PerlinNoise_2D(float x, float y);

class world :public chunk_manager
{
public:
	world() :chunk_manager(this)
	{

	}
	void buildChunk(chunk* chunk)
	{
		chunk->getBlock(7, 7, 7)->setBlockID(1);
		chunk->getBlock(7, 7, 7)->setBlockLight(5);

		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				int height = 50 - PerlinNoise_2D(i + chunk->getChunkX() * 16, j + chunk->getChunkZ() * 16) * 10;

				if (height < chunk->getChunkY() * 16)
					height = 0;

				if (height > (chunk->getChunkY() + 1) * 16)
					height = 16;

				for (int k = 0; k < 16; k++)
				{
					chunk->getBlock(i, k, j)->setBlockLight(15);
				}

				for (int k = 0; k < height - chunk->getChunkY() * 16; k++)
				{
					chunk->getBlock(i, k, j)->setBlockID(1);
					chunk->getBlock(i, k, j)->setBlockLight(0);
				}
			}
		}
		/*
		if (chunk->getChunkY() == 0)
		{
			for (uint8_t i = 0; i < 16; i++)
				for (uint8_t j = 0; j < 16; j++)
					chunk->getBlock(i, 0, j)->setBlockID(1);

			for (uint8_t i = 0; i < 16; i++)
				for (uint8_t j = 0; j < 16; j++)
					chunk->getBlock(i, 2, j)->setBlockID(32);
		}*/
		chunk->_isNewChunk.store(false);
	}
};