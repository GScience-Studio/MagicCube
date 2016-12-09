
#include "ChunkRender.h"

#define HIDE_TOP		0x01
#define HIDE_DOWM		0x02
#define HIDE_LEFT		0x04
#define HIDE_RIGHT		0x08
#define HIDE_BACK		0x10
#define HIDE_FRONT		0x20
#define NO_ALPHA_BLOCK	0x40

chunk_render::chunk_render(blockRenderData* block): render_node(chunkRenderProgram)
{
	std::vector<blockRenderData> blockRenderList;
	
	for (unsigned short j = 0; j < 4096; j++)
	{
		block[j].setBlockRenderData(j, 0);

		uint8_t posX = getChunkBlockX(j);
		uint8_t posY = getChunkBlockY(j);
		uint8_t posZ = getChunkBlockZ(j);
		
		if (j != blockChunkLocationToShort(posX, posY, posZ))
		{
			return;
		}
		block[j].setNearbyBlockLight(posZ, posZ, posZ, posZ, posZ, posZ);

		if ((posY % 2 != 0 || (posX == 15) || (posZ == 15)) && posX != 14 && posZ != 14)
			blockRenderList.push_back(block[j]);
	}
	
	setBlockRenderDatas(&blockRenderList[0], blockRenderList.size());

	_blockCount = (unsigned short)blockRenderList.size();
}

void chunk_render::setBlockRenderDatas(const blockRenderData* blockRenderData, const GLuint blockCount)
{
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, sizeof(GLuint) * 2 * blockCount, blockRenderData, _getRenderProgram());
}