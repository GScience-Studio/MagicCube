#pragma once

#include "Chunk.h"
#include <unordered_map>

class chunk_manager 
{
private:
	std::unordered_map<chunk_location,chunk*, chunk_location_hash, chunk_location_compare> _chunkList;

public:
	chunk* addChunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
	{
		if (_chunkList[{chunkX, chunkY, chunkZ}] != nullptr)
			throw(std::runtime_error("1"));

		chunk* newChunk = new chunk(chunkX, chunkY, chunkZ);

		_chunkList[{chunkX, chunkY, chunkZ}] = newChunk;

		return newChunk;
	}
	void clear()
	{
		for (auto chunk = _chunkList.begin(); chunk != _chunkList.end(); chunk++)
		{
			delete (*chunk).second;
		}
		_chunkList.clear();
	}
	chunk* getChunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ)
	{
		return _chunkList[{chunkX, chunkY, chunkZ}];
	}
	~chunk_manager()
	{
		for (auto chunk = _chunkList.begin(); chunk != _chunkList.end(); chunk++)
		{
			delete (*chunk).second;
		}
	}
};