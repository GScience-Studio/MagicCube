#pragma once

#define SIGHT 16

#include "WorldManager\World.h"
#include "WorldManager\Location.h"

class world_manager
{
private:
	location _playerLocation;

	bool _isChunkInSight(const chunk& inChunk) const
	{
		return abs(inChunk.getChunkX() - _playerLocation._x) > SIGHT ||
			abs(inChunk.getChunkY() - _playerLocation._y) > SIGHT;
	}
public:
	world_manager() :_playerLocation(&testWorld, 0, 0, 0) {}

	world testWorld;

	void transport(const location& location)
	{
		_playerLocation = location;
	}

	void tickListener()
	{
		//check chunks
		for (unsigned int i = 0; i < SIGHT * 2; i++)
			for (unsigned int j = 0; j < SIGHT * 2; j++)
				for (unsigned int k = 0; k < 16; k++)
					_playerLocation._world->getChunk(_playerLocation._x + SIGHT - i, k, _playerLocation._z + SIGHT - j);
	}
};