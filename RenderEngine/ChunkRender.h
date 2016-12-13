#pragma once

#define CHUNK_RENDER_PRIORITY 0.001f
#define CHUNK_HALF_ALPHA_BLOCK_RENDER_PRIORITY 0.0f

#include "../ChunkUniversal.h"
#include "RenderNode.h"
#include "ChunkRenderShader.h"
#include "SceneNode.h"

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

class chunk_render : public render_node
{
private:
	//add a half-alpha block render node
	chunk_render() : render_node(chunkRenderProgram) {}

	chunk_render* _halfAlphaBlockRenderNode = nullptr;

	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned short	_blockCount = 0;

	//draw chunk
	void _draw(camera _golbalCamera)
	{
		//is alpha block render node?
		if (_halfAlphaBlockRenderNode == nullptr)
		{
			_glInstance.useTexture(*_getTexture());
			_getRenderProgram()->drawBuffer(0, _blockCount, *_getBuffer(), _golbalCamera + _nodeCamera, _modelLocation);
		}
		else
		{
			_glInstance.useTexture(*_getTexture());
			_getRenderProgram()->drawBuffer(0, _blockCount, *_getBuffer(), _golbalCamera + _nodeCamera, _modelLocation);
		}
	}
public:
	//add a chunk render
	chunk_render(scene_node* chunkSceneNode) : render_node(chunkRenderProgram)
	{
		//add half-alpha render node
		_halfAlphaBlockRenderNode = new chunk_render();

		//set priority
		_priority = CHUNK_RENDER_PRIORITY;
		
		_halfAlphaBlockRenderNode->_priority = CHUNK_HALF_ALPHA_BLOCK_RENDER_PRIORITY;

		chunkSceneNode->addRenderNode(_halfAlphaBlockRenderNode);
	}

	/*
	* set chunk location
	* made by GM2000
	*/
	void setChunkLocation(int x, int y, int z)
	{
		getModelCamera()->getLocation()->moveTo(x * 16, y * 16, z * 16);

		if (_halfAlphaBlockRenderNode != nullptr)
			_halfAlphaBlockRenderNode->getModelCamera()->getLocation()->moveTo(x * 16, y * 16, z * 16);
	}

	/*
	* create chunk render by a list of block render data
	* made by GM2000
	*/
	chunk_render(scene_node* chunkSceneNode, blockRenderData* block);

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