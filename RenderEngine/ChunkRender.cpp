
#include "ChunkRender.h"

#define HIDE_TOP		0x01
#define HIDE_DOWM		0x02
#define HIDE_LEFT		0x04
#define HIDE_RIGHT		0x08
#define HIDE_BACK		0x10
#define HIDE_FRONT		0x20

chunk_render::chunk_render(unsigned char sight) :_sight(sight), render_node(chunkRenderProgram)
{
	blockRenderData* block = new blockRenderData[4096];

	std::vector<blockRenderData> blockRenderList;

	for (unsigned j = 0; j < 4096; j++)
	{
		block[j].setBlockRenderData(j, 0);

		block[j].nearbyBlockInfo = 0xFFFFFF00;

		unsigned short posY = j / 256u;
		unsigned short posX = (j - posY * 256u) / 16u;
		unsigned short posZ = (j - posY * 256u) - posX * 16u;

		if (posZ < 15)
			block[j].nearbyBlockInfo |= HIDE_RIGHT;

		if (posZ > 0)
			block[j].nearbyBlockInfo |= HIDE_LEFT;

		if (posY < 15)
			block[j].nearbyBlockInfo |= HIDE_TOP;

		if (posY > 0)
			block[j].nearbyBlockInfo |= HIDE_DOWM;

		if (posX < 15)
			block[j].nearbyBlockInfo |= HIDE_FRONT;

		if (posX > 0)
			block[j].nearbyBlockInfo |= HIDE_BACK;

		if (!(
			(block[j].nearbyBlockInfo && HIDE_RIGHT)==
			(block[j].nearbyBlockInfo && HIDE_LEFT)	==
			(block[j].nearbyBlockInfo && HIDE_TOP)	==
			(block[j].nearbyBlockInfo && HIDE_DOWM)	==
			(block[j].nearbyBlockInfo && HIDE_FRONT)==
			(block[j].nearbyBlockInfo && HIDE_BACK)	== 0))
			blockRenderList.push_back(block[j]);
	}
	setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	delete[]block;
}

void chunk_render::setBlockRenderDatas(const blockRenderData* blockRenderData, const GLuint blockCount)
{
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, sizeof(GLuint) * 2 * blockCount, blockRenderData, _getRenderProgram());
}