#pragma once

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"

class chunk_global_render : public render_node
{
	friend class chunk_render;

private:
	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned short	_blockCount = 0;
	unsigned short	_blockStart = 0;

	//draw chunk
	void _draw(camera_synchronize _golbalCamera)
	{
		if (_blockCount - _blockStart == 0)
			return;

		_glInstance.useTexture(*_getTexture());

		_getRenderProgram()->drawBuffer(_blockStart, _blockCount, *_getBuffer(), _golbalCamera + _nodeCamera, _modelLocation);
	}
public:
	//add a normal chunk render and auto gen buffer
	chunk_global_render(float priority) : render_node(chunkRenderProgram)
	{
		//set priority
		_priority = priority;
	}

	//add a normal chunk render and set buffer by user
	chunk_global_render(float priority, buffer* buffer) : render_node(buffer, chunkRenderProgram)
	{
		//set priority
		_priority = priority;
	}

	/*
	* set chunk location
	* made by GM2000
	*/
	void setChunkLocation(int x, int y, int z)
	{
		getModelCamera()->getLocation()->moveTo(x * 16, y * 16, z * 16);
	}

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
	void setBlockRenderDatas(const void* blockRenderData, const GLuint blockCount)
	{
		gl_manager::getInstance().bufferData(*_getBuffer(), 0, sizeof(GLuint) * 2 * blockCount, blockRenderData, _getRenderProgram());
	}
};