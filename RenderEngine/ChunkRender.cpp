
#include "ChunkRender.h"

#include <list>

#define HIDE_TOP			0x01
#define HIDE_DOWM			0x02
#define HIDE_LEFT			0x04
#define HIDE_RIGHT			0x08
#define HIDE_BACK			0x10
#define HIDE_FRONT			0x20
#define HALF_ALPHA_BLOCK	0x40

chunk_render::chunk_render(scene_node* sceneNode, texture* blockTexture) : _sceneNode(sceneNode)
{
	chunkGlobalRender = new chunk_global_render(CHUNK_RENDER_PRIORITY, false);
	chunkHalfAlphaBlockRender = new chunk_global_render(CHUNK_HALF_ALPHA_BLOCK_RENDER_PRIORITY, true, chunkGlobalRender->_getBuffer());

	chunkGlobalRender->bindTexture(blockTexture);
	chunkHalfAlphaBlockRender->bindTexture(blockTexture);
}

void chunk_render::setBlockRenderDatas(block_render_data* block, unsigned short count)
{
	std::vector<block_render_data> blockRenderList(count);

	unsigned short alphaBlockCount		= 0;
	unsigned short noAlphaBlockCount	= 0;

	for (unsigned short i = 0; i < count; i++)
	{
		if ((block[i].nearbyBlockInfo & HIDE_TOP) && 
			(block[i].nearbyBlockInfo & HIDE_DOWM) && 
			(block[i].nearbyBlockInfo & HIDE_LEFT) && 
			(block[i].nearbyBlockInfo & HIDE_RIGHT) && 
			(block[i].nearbyBlockInfo & HIDE_BACK) && 
			(block[i].nearbyBlockInfo & HIDE_FRONT) ||
			(block[i].blockInfo >> 12 == 0))
			continue;

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
	//remove empty block
	if (alphaBlockCount + noAlphaBlockCount != count)
		blockRenderList.erase(blockRenderList.begin() + noAlphaBlockCount, blockRenderList.begin() + count - noAlphaBlockCount - alphaBlockCount);
	
	if (blockRenderList.size() == 0)
		return;

	chunkGlobalRender->setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	chunkGlobalRender->setBufferUseInfo(0, noAlphaBlockCount);
	chunkHalfAlphaBlockRender->setBufferUseInfo(noAlphaBlockCount, blockRenderList.size());

	_sceneNode->addRenderNode(chunkGlobalRender);
	_sceneNode->addRenderNode(chunkHalfAlphaBlockRender);
}

void block_render_data::setAlpha(bool hasAlpha)
{
	if (hasAlpha)
		nearbyBlockInfo |= HALF_ALPHA_BLOCK;
	else if(nearbyBlockInfo & HALF_ALPHA_BLOCK)
		nearbyBlockInfo ^= HALF_ALPHA_BLOCK;
}

void block_render_data::setNearbyBlockAlpha(bool top, bool down, bool left, bool right, bool front, bool back)
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