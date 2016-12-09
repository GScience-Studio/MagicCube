#pragma once

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"

struct blockRenderData
{
	unsigned int	blockInfo;
	unsigned int	nearbyBlockInfo;

	void setBlockRenderData(unsigned short blockLocation, unsigned short blockID)
	{
#ifdef _DEBUG
		if (blockLocation >= 4096)
			message("[Error]Fail to create new block render date because \"blockLocation\" can't large than 4096", msgError, false);
#endif
		blockInfo = blockLocation;

		blockInfo += (blockID << 12);
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
	chunk_render();

	/*
	* set light pos
	* from the input location to 0,0,0
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