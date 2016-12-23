#pragma once

#include "World.h"

class location
{
private:
	world* _world;

	int32_t _x;
	int32_t _y;
	int32_t _z;

public:
	world* getWorld() const
	{
		return _world;
	}

	int32_t getX() const
	{
		return _x;
	}
	int32_t getY() const
	{
		return _y;
	}
	int32_t getZ() const
	{
		return _z;
	}

	int32_t getChunkX() const
	{
		return _x > 0 ? _x / 16 : _x / 16 - 1;
	}
	int32_t getChunkY() const
	{
		return _y / 16;
	}
	int32_t getChunkZ() const
	{
		return _z > 0 ? _z / 16 : _z / 16 - 1;
	}
	location(world* world, int32_t x, int32_t y, int32_t z)
	{
		_world = world;

		_x = x;
		_y = y;
		_z = z;
	}
};