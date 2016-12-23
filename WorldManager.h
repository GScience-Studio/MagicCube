#pragma once

#define SIGHT 16

#include "WorldManager\World.h"
#include "WorldManager\Location.h"
#include <string.h>

class world_manager
{
private:
	std::map<std::string, world*> _worldMap;

	location _playerLocation = location(nullptr, 0, 0, 0);

	int32_t _lastChunkX;
	int32_t _lastChunkZ;

	bool _needRefreshChunk = true;

	bool _isChunkInSight(const chunk& inChunk) const
	{
		return abs(inChunk.getChunkX() - _playerLocation.getX()) < SIGHT &&
			abs(inChunk.getChunkZ() - _playerLocation.getZ()) < SIGHT;
	}

	chunk* _randomGetChunk(const world& world) const
	{
		auto it = world._chunkMap.begin();
		std::advance(it, rand() % world._chunkMap.size());

		return it->second;
	}
public:
	world* loadWorld(std::string worldName)
	{
		world* newWorld = new world();

		_worldMap[worldName] = newWorld;

		return newWorld;
	}
	void unloadWorld(std::string worldName)
	{
		_worldMap.erase(worldName);
	}

	void transport(const location& location)
	{
		_needRefreshChunk = (_lastChunkX != location.getChunkX() || _lastChunkZ != location.getChunkZ());

		_lastChunkX = location.getChunkX();
		_lastChunkZ = location.getChunkZ();

		_playerLocation = location;
	}

	void refreshWorld()
	{
		if (_playerLocation.getWorld() == nullptr)
			return;

		//if has too much chunk try to unload them with random tick
		if (_playerLocation.getWorld()->_chunkMap.size() > SIGHT * SIGHT * 5)
		{
			chunk* randomGetChunk = _randomGetChunk(*_playerLocation.getWorld());

			if (!_isChunkInSight(*randomGetChunk))
				_playerLocation.getWorld()->unloadChunk(randomGetChunk);
		}
		//check chunks
		if (_needRefreshChunk)
			for (unsigned int i = 0; i < SIGHT * 2 - 1; i++)
				for (unsigned int j = 0; j < SIGHT * 2 - 1; j++)
					for (unsigned int k = 0; k < 16; k++)
						_playerLocation.getWorld()->getChunk(_playerLocation.getX() + SIGHT - i - 1, k, _playerLocation.getZ() + SIGHT - j - 1);
		else
			return;

		_needRefreshChunk = false;
	}
	~world_manager()
	{
		for (auto world = _worldMap.begin(); world != _worldMap.end(); world++)
		{
			delete (*world).second;
		}
	}
};