#pragma once

#include "World.h"

struct location
{
	world* _world;

	int32_t _x;
	int32_t _y;
	int32_t _z;

	location(world* world, int32_t x, int32_t y, int32_t z)
	{
		_world = world;

		_x = x;
		_y = y;
		_z = z;
	}
};