
#include "ChunkRender.h"

#define HIDE_TOP			0x01
#define HIDE_DOWM			0x02
#define HIDE_LEFT			0x04
#define HIDE_RIGHT			0x08
#define HIDE_BACK			0x10
#define HIDE_FRONT			0x20
#define HALF_ALPHA_BLOCK	0x40

chunk_render::chunk_render(scene_node* sceneNode, texture* blockTexture)
{
	chunkGlobalRender = new chunk_global_render(CHUNK_RENDER_PRIORITY, false);
	chunkHalfAlphaBlockRender = new chunk_global_render(CHUNK_HALF_ALPHA_BLOCK_RENDER_PRIORITY, true, chunkGlobalRender->_getBuffer());

	chunkGlobalRender->bindTexture(blockTexture);
	chunkHalfAlphaBlockRender->bindTexture(blockTexture);

	sceneNode->addRenderNode(chunkGlobalRender);
	sceneNode->addRenderNode(chunkHalfAlphaBlockRender);
}

void chunk_render::setBlockRenderDatas(blockRenderData* block)
{
	std::vector<blockRenderData> blockRenderList;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			uint16_t blockLocation = blockChunkLocationToShort(i, 2, j);

			block[blockLocation].setBlockRenderData(blockLocation, 0);
			block[blockLocation].nearbyBlockInfo = HIDE_LEFT | HIDE_RIGHT | HIDE_BACK | HIDE_FRONT;
			block[blockLocation].setNearbyBlockLight(15, 15, 15, 15, 15, 15);

			blockRenderList.push_back(block[blockLocation]);
		}
	}

	chunkGlobalRender->_blockStart = 0;
	chunkGlobalRender->_blockEnd = (unsigned short)blockRenderList.size();

	chunkHalfAlphaBlockRender->_blockStart = (unsigned short)blockRenderList.size();

	chunkGlobalRender->setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	chunkHalfAlphaBlockRender->_blockEnd = (unsigned short)blockRenderList.size();
}