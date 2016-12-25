#pragma once

#include "World.h"

class location
{
private:
	world* _world;

	double _x;
	double _y;
	double _z;

public:
	world* getWorld() const
	{
		return _world;
	}

	double getX() const
	{
		return _x;
	}
	double getY() const
	{
		return _y;
	}
	double getZ() const
	{
		return _z;
	}

	int32_t getChunkX() const
	{
		return _x >= 0 ? (int32_t)_x / 16 : (int32_t)_x / 16 - 1;
	}
	int32_t getChunkY() const
	{
		return (int32_t)_y / 16;
	}
	int32_t getChunkZ() const
	{
		return _z >= 0 ? (int32_t)_z / 16 : (int32_t)_z / 16 - 1;
	}
	location(world* world, double x, double y, double z)
	{
		_world = world;

		_x = x;
		_y = y;
		_z = z;
	}
};