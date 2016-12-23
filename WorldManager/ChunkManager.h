#pragma once

#include "Chunk.h"
#include <iostream>
#include <map>

class world;

class chunk_manager 
{
	friend class world_manager;

private:
	std::map<chunk_location, chunk*> _chunkList;

	world* _world;

protected:
	chunk_manager(world* world)
	{
		_world = world;
	}

public:
	chunk* addChunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
	{
		chunk* newChunk = new chunk(chunkX, chunkY, chunkZ, _world);

		_chunkList[{chunkX, chunkY, chunkZ}] = newChunk;

#ifdef _DEBUG
		std::cout << "Load a new chunk at:" << chunkX << "," << chunkY << "," << chunkZ << std::endl;
#endif
		return newChunk;
	}
	chunk* getChunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
	{
		//has this chunk?
		auto getChunk = _chunkList.find({ chunkX, chunkY, chunkZ });

		if (getChunk != _chunkList.end())
			return getChunk->second;

		//create one
		return addChunk(chunkX, chunkY, chunkZ);
	}
	void unloadChunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
	{
		auto getChunk = _chunkList.find({ chunkX, chunkY, chunkZ });

		if (getChunk == _chunkList.end())
			return;

		_chunkList.erase(getChunk);
	}
	void unloadChunk(chunk* chunk)
	{
		unloadChunk(chunk->getChunkX(), chunk->getChunkY(), chunk->getChunkZ());
	}
	~chunk_manager()
	{
		for (auto chunk = _chunkList.begin(); chunk != _chunkList.end(); chunk++)
		{
			delete (*chunk).second;
		}
	}
};