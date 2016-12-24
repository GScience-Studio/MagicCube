#pragma once

#include "../WorldManager.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../GSRenderEngine.h"

class game_world_manager :public world_manager
{
private:
	chunk_render*				_chunkRenderList[(SIGHT * 2 - 1) * (SIGHT * 2 - 1) * 16];
	std::vector<chunk_render*>	_emptyChunkRenderList;

	scene_node* _scene;

	void _renderChunk(chunk* chunk, chunk_render* chunkRender)
	{
		block_render_data blockRenderData[4096];

		for (unsigned char i = 0; i < 16; i++)
			for (unsigned char j = 0; j < 16; j++)
				for (unsigned char k = 0; k < 16; k++)
				{
					block* getBlock = chunk->getBlock(i, j, k);
					block_render_data* getBlockRenderData = &blockRenderData[blockChunkLocationToShort(i, j, k)];

					getBlockRenderData->setBlockRenderData(blockChunkLocationToShort(i, j, k), getBlock->getBlockID());

					if (getBlock->getBlockID() != 0)
						getBlockRenderData->setNearbyBlockAlpha(true, true, true, true, true, true);
				}
		chunkRender->setChunkLocation(chunk->getChunkX(), chunk->getChunkY(), chunk->getChunkZ());
		chunkRender->setBlockRenderDatas(blockRenderData, 4096);
	}
public:
	void transport(world* world, double x, double y, double z)
	{
		world_manager::transport(location(world, x, y, z));
	}
	void refreshGameWorld()
	{
		for (unsigned int i = 0; i < ((SIGHT * 2 - 1) * (SIGHT * 2 - 1) * 16); i++)
		{
			if (!_isChunkInSight(_chunkRenderList[i]->getChunkRenderX(), _chunkRenderList[i]->getChunkRenderZ()))
			{
				if (std::find(_emptyChunkRenderList.begin(), _emptyChunkRenderList.end(), _chunkRenderList[i]) == _emptyChunkRenderList.end())
					_emptyChunkRenderList.push_back(_chunkRenderList[i]);
			}
		}
		for (unsigned int i = 0; i < _newChunkList.size(); i++)
		{
			if (_emptyChunkRenderList.size() == 0)
				break;

			_renderChunk(_newChunkList.back(), _emptyChunkRenderList.back());

			_newChunkList.pop_back();
			_emptyChunkRenderList.pop_back();
		}
		refreshWorld();
	}
	~game_world_manager()
	{
		for (unsigned int i = 0; i < ((SIGHT * 2 - 1) * (SIGHT * 2 - 1) * 16); i++)
		{
			delete(_chunkRenderList[i]);
		}
	}
	game_world_manager(scene_node* scene, texture* texture)
	{
		_scene = scene;

		for (unsigned int i = 0; i < ((SIGHT * 2 - 1) * (SIGHT * 2 - 1) * 16); i++)
		{
			_chunkRenderList[i] = new chunk_render(scene, texture);
			_chunkRenderList[i]->setChunkLocation(i, 0, 0);
		}
	}
};