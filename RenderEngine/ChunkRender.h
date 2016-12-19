#pragma once

#define CHUNK_RENDER_PRIORITY 0.501f
#define CHUNK_HALF_ALPHA_BLOCK_RENDER_PRIORITY 0.5f

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"
#include "ChunkGlobalRender.h"
#include "SceneNode.h"

struct blockRenderData
{
	unsigned int	blockInfo = 0;
	unsigned int	nearbyBlockInfo = 0;

	blockRenderData()
	{
		setNearbyBlockAlpha(false, false, false, false, false, false);
	}
	void setBlockRenderData(uint16_t blockLocation, uint16_t blockID)
	{
#ifdef _DEBUG
		if (blockLocation >= 4096)
			message("[Error]Fail to create new block render date because \"blockLocation\" can't large than 4096", msgError, false);
#endif
		blockInfo = blockLocation;

		blockInfo += (blockID << 12);
	}
	void setNearbyBlockLight(uint8_t blockUp, uint8_t blockDown, uint8_t blockLeft, uint8_t blockRight, uint8_t blockFront, uint8_t blockBack)
	{
		nearbyBlockInfo += (blockUp + (blockDown << 4) + (blockLeft << 8) + (blockRight << 12) + (blockFront << 16) + (blockBack << 20)) << 8;
	}
	void setAlpha(bool hasAlpha);
	void setNearbyBlockAlpha(bool top, bool down, bool left, bool right, bool front, bool back);
};

class chunk_render
{
	chunk_global_render* chunkGlobalRender;
	chunk_global_render* chunkHalfAlphaBlockRender;

public:
	void setBlockRenderDatas(blockRenderData* block, unsigned short count);

	void setChunkLocation(int x, int y, int z)
	{
		chunkGlobalRender->setChunkLocation(x, y, z);
		chunkHalfAlphaBlockRender->setChunkLocation(x, y, z);
	}

	chunk_render(scene_node* sceneNode, texture* blockTexture);
};