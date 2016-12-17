
#include "ChunkRender.h"

#include <list>

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

void chunk_render::setBlockRenderDatas(blockRenderData* block, unsigned short count)
{
	std::vector<blockRenderData> blockRenderList(count);

	unsigned short alphaBlockCount		= 0;
	unsigned short noAlphaBlockCount	= 0;

	for (unsigned short i = 0; i < count; i++)
	{
		if (block[i].nearbyBlockInfo & HALF_ALPHA_BLOCK)
		{
			alphaBlockCount++;

			blockRenderList[count - alphaBlockCount] = block[i];
		}
		else
		{
			blockRenderList[noAlphaBlockCount] = block[i];

			noAlphaBlockCount++;
		}
	}
	chunkGlobalRender->setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	chunkGlobalRender->setBufferUseInfo(0, noAlphaBlockCount);
	chunkHalfAlphaBlockRender->setBufferUseInfo(noAlphaBlockCount, count);
}

void blockRenderData::setAlpha(bool hasAlpha)
{
	if (hasAlpha)
		nearbyBlockInfo |= HALF_ALPHA_BLOCK;
	else if(nearbyBlockInfo & HALF_ALPHA_BLOCK)
		nearbyBlockInfo ^= HALF_ALPHA_BLOCK;
}

void blockRenderData::setNearbyBlockAlpha(bool top, bool down, bool left, bool right, bool front, bool back)
{
	nearbyBlockInfo = nearbyBlockInfo >> 6 << 6;

	if (!top)
		nearbyBlockInfo |= HIDE_TOP;

	if (!down)
		nearbyBlockInfo |= HIDE_DOWM;

	if (!left)
		nearbyBlockInfo |= HIDE_LEFT;

	if (!right)
		nearbyBlockInfo |= HIDE_RIGHT;

	if (!front)
		nearbyBlockInfo |= HIDE_FRONT;

	if (!back)
		nearbyBlockInfo |= HIDE_BACK;
}