#pragma once

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"

class chunk_global_render : public render_node
{
	friend class chunk_render;

private:
	gl_manager& _glInstance = gl_manager::getInstance();

	std::mutex lock;

	unsigned short	_blockEnd	= 0;
	unsigned short	_blockStart = 0;

	bool _hasHalfAlpha = false;

	//draw chunk
	void _draw(camera _golbalCamera)
	{
		lock.lock();

		unsigned short bufferStart = _blockStart;
		unsigned short bufferEnd = _blockEnd - _blockStart;

		lock.unlock();

		if (bufferEnd <= 0 || _getBuffer()->getSize() < bufferEnd || _getBuffer()->getSize() < bufferStart)
			return;

		_glInstance.useTexture(*_getTexture());

		if (_hasHalfAlpha)
		{
			glDepthMask(GL_FALSE);

			_getRenderProgram()->drawBuffer(bufferStart, _blockEnd - _blockStart, *_getBuffer(), camera(), _modelLocation);

			glDepthMask(GL_TRUE);
		}
		else
		{
			_getRenderProgram()->drawBuffer(bufferStart, _blockEnd - _blockStart, *_getBuffer(), camera(), _modelLocation);
		}
	}
public:
	//add a normal chunk render and auto gen buffer
	chunk_global_render(float priority, bool hasHalfAlpha) : render_node(chunkRenderProgram), _hasHalfAlpha(hasHalfAlpha)
	{
		//set priority
		_priority = priority;
	}

	//add a normal chunk render and set buffer by user
	chunk_global_render(float priority, bool hasHalfAlpha, buffer* buffer) : render_node(buffer, chunkRenderProgram), _hasHalfAlpha(hasHalfAlpha)
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
	* this function might be remove
	*/
	void setLight(float x, float y, float z)
	{
		((chunk_render_program*)_getRenderProgram())->setLight(-x, y, -z);
	}

	void setBufferUseInfo(unsigned short start, unsigned short end)
	{
		lock.lock();

		_blockStart = start;
		_blockEnd	= end;

		lock.unlock();
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