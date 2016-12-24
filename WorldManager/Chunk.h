#pragma once

#include "../ChunkUniversal.h"
#include "Block.h"
#include <initializer_list>
#include <string>
#include <sstream>

class world;

struct chunk_location
{
	const int32_t _chunkX;
	const int32_t _chunkY;
	const int32_t _chunkZ;

	chunk_location(int32_t chunkX, int32_t chunkY, int32_t chunkZ) : _chunkX(chunkX), _chunkY(chunkY), _chunkZ(chunkZ) {}
	chunk_location(std::initializer_list<int32_t> chunkLocationList) : chunk_location(*chunkLocationList.begin(), *(chunkLocationList.begin() + 1), *(chunkLocationList.begin() + 2)) {}

	bool operator ==(const chunk_location& chunkLocation) const
	{
		return (
			(chunkLocation._chunkX == _chunkX) &&
			(chunkLocation._chunkY == _chunkY) &&
			(chunkLocation._chunkZ == _chunkZ));
	}
	bool operator <(const chunk_location& chunkLocation) const
	{
		if (chunkLocation._chunkX < _chunkX)
			return true;
		else if (chunkLocation._chunkX == _chunkX)
			if (chunkLocation._chunkY < _chunkY)
				return true;
			else if (chunkLocation._chunkY == _chunkY)
				if (chunkLocation._chunkZ < _chunkZ)
					return true;
				else if (chunkLocation._chunkZ == _chunkZ)
					return false;

		return false;
	}
};

class chunk
{
	friend class chunk_manager;

private:
	chunk_location	chunkLocation;

	block* _blockList;
	world* _world;

	chunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ, world* world) : chunkLocation(chunkX, chunkY, chunkZ)
	{
		_blockList = new block[4096];
		_world = world;

		if (chunkY < 2)
			_blockList[0].setBlockID(1);
	}
	~chunk()
	{
		delete[](_blockList);
	}
public:
	bool _hasRender = false;

	int32_t getChunkX() const
	{
		return chunkLocation._chunkX;
	}
	int32_t getChunkY() const
	{
		return chunkLocation._chunkY;
	}
	int32_t getChunkZ() const
	{
		return chunkLocation._chunkZ;
	}

	world* getWorld() const
	{
		return _world;
	}

	//you'd better don't save the pointer it return
	block* getBlock(uint8_t x, uint8_t y, uint8_t z)
	{
		return &_blockList[blockChunkLocationToShort(x, y, z)];
	}
};