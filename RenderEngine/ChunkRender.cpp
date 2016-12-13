
#include "ChunkRender.h"

#define HIDE_TOP		0x01
#define HIDE_DOWM		0x02
#define HIDE_LEFT		0x04
#define HIDE_RIGHT		0x08
#define HIDE_BACK		0x10
#define HIDE_FRONT		0x20
#define NO_ALPHA_BLOCK	0x40

chunk_render::chunk_render(scene_node* chunkSceneNode, blockRenderData* block): chunk_render(chunkSceneNode)
{
	std::vector<blockRenderData> blockRenderList;
	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			uint16_t blockLocation = blockChunkLocationToShort(i, 0, j);

			block[blockLocation].setBlockRenderData(blockLocation, 0);
			block[blockLocation].nearbyBlockInfo = HIDE_LEFT | HIDE_RIGHT | HIDE_BACK | HIDE_FRONT;
			block[blockLocation].setNearbyBlockLight(15, 0, 0, 0, 0, 0);

			blockRenderList.push_back(block[blockLocation]);
		}
	}
	uint16_t blockLocation = blockChunkLocationToShort(0, 5, 0);

	block[blockLocation].setBlockRenderData(blockLocation, 0);
	block[blockLocation].setNearbyBlockLight(15, 15, 15, 15, 15, 15);

	blockRenderList.push_back(block[blockLocation]);

	setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	_blockCount = (unsigned short)blockRenderList.size();

	if (_halfAlphaBlockRenderNode == nullptr)
		return;

	blockRenderList.clear();

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			uint16_t blockLocation = blockChunkLocationToShort(i, 3, j);

			block[blockLocation].setBlockRenderData(blockLocation, 1);
			block[blockLocation].nearbyBlockInfo = HIDE_LEFT | HIDE_RIGHT | HIDE_BACK | HIDE_FRONT;
			block[blockLocation].setNearbyBlockLight(15, 15, 15, 15, 15, 15);

			blockRenderList.push_back(block[blockLocation]);
		}
	}

	_halfAlphaBlockRenderNode->setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	_halfAlphaBlockRenderNode->_blockCount = (unsigned short)blockRenderList.size();
}

void chunk_render::setBlockRenderDatas(const blockRenderData* blockRenderData, const GLuint blockCount)
{
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, sizeof(GLuint) * 2 * blockCount, blockRenderData, _getRenderProgram());
}