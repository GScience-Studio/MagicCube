#pragma once

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"

struct blockRenderData
{
	unsigned int	blockInfo = 0;
	unsigned int	nearbyBlockInfo = 0;

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
};

class chunk_render :public render_node
{
private:
	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned short	_blockCount = 0;

	void _draw(camera _golbalCamera)
	{
		_glInstance.useTexture(*_getTexture());
		
		_getRenderProgram()->drawBuffer(0, _blockCount, *_getBuffer(), _golbalCamera + _nodeCamera, _modelLocation);
	}
public:
	chunk_render() : render_node(chunkRenderProgram) {}

	/*
	* create chunk render by a list of block render data
	* made by GM2000
	*/
	chunk_render(blockRenderData* block);

	/*
	* set light pos
	* from the input location to 0,0,0
	* this function might bu remove
	*/
	void setLight(float x, float y, float z)
	{
		((chunk_render_program*)_getRenderProgram())->setLight(-x, y, -z);
	}

	/*
	* set blocks render datas
	* made by GM2000
	*/
	void setBlockRenderDatas(const blockRenderData* blockRenderData, const GLuint blockCount);
};