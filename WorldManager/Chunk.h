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
};

class chunk_location_hash
{
public:
	size_t operator()(const chunk_location& location) const
	{
		unsigned long __h = 0;

		__h = __h + location._chunkX;
		__h = 5 * __h + location._chunkY;
		__h = 5 * __h + location._chunkZ;

		return size_t(__h);
	}
};


class chunk_location_compare
{
public:
	bool operator()(const chunk_location& location1, const chunk_location& location2)const
	{
		return location1 == location2;
	}
};

class chunk
{
	friend class chunk_manager;

private:
	chunk_location chunkLocation;

	block* _blockList;

	world* _world;

	chunk(int32_t chunkX, int32_t chunkY, int32_t chunkZ) : chunkLocation(chunkX, chunkY, chunkZ)
	{
		_blockList = new block[4096];
	}
	~chunk()
	{
		delete[](_blockList);
	}
public:
	int32_t getChunkX()
	{
		return chunkLocation._chunkX;
	}
	int32_t getChunkY()
	{
		return chunkLocation._chunkY;
	}
	int32_t getChunkZ()
	{
		return chunkLocation._chunkZ;
	}
	//you'd better don't save the pointer it return
	block* getBlock(uint8_t x, uint8_t y, uint8_t z)
	{
		return &_blockList[blockChunkLocationToShort(x, y, z)];
	}
	world* getWorld()
	{
		return _world;
	}
};