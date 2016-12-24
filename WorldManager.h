#pragma once

#define SIGHT 3

#include "WorldManager\World.h"
#include "WorldManager\Location.h"
#include <vector>
#include <string.h>

class world_manager
{
protected:
	std::map<std::string, world*> _worldMap;

	std::vector<chunk*> _newChunkList;

	location _playerLocation = location(nullptr, 0, 0, 0);

	int32_t _lastChunkX;
	int32_t _lastChunkZ;

	bool _needRefreshAllRenderData = true;
	bool _needRefreshChunk = true;

	bool _isChunkInLastSight(int chunkX, int chunkZ) const
	{
		return abs(chunkX - _lastChunkX) < SIGHT &&
			abs(chunkZ - _lastChunkZ) < SIGHT;
	}

	bool _isChunkInSight(int chunkX, int chunkZ) const
	{
		return abs(chunkX - _playerLocation.getChunkX()) < SIGHT &&
			abs(chunkZ - _playerLocation.getChunkZ()) < SIGHT;
	}

	bool _isChunkInSight(const chunk& inChunk) const
	{
		return _isChunkInSight(inChunk.getChunkX(), inChunk.getChunkZ());
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

	void transport(const location& inLocation)
	{
		_needRefreshChunk = (_lastChunkX != inLocation.getChunkX() || _lastChunkZ != inLocation.getChunkZ() || _needRefreshChunk);

		_lastChunkX = _playerLocation.getChunkX();
		_lastChunkZ = _playerLocation.getChunkZ();

		if (inLocation.getWorld() != nullptr)
			_playerLocation = inLocation;
		else
			_playerLocation = location(_playerLocation.getWorld(), inLocation.getX(), inLocation.getY(), inLocation.getZ());
	}

	void refreshWorld()
	{
		if (_playerLocation.getWorld() == nullptr)
			return;

		//if has too much chunk try to unload them with random tick
		if (_playerLocation.getWorld()->_chunkMap.size() > (SIGHT + 5) * (SIGHT + 5) * 16)
		{
			chunk* randomGetChunk = _randomGetChunk(*_playerLocation.getWorld());

			if (!_isChunkInSight(*randomGetChunk))
				_playerLocation.getWorld()->unloadChunk(randomGetChunk);
		}
		//check chunks
		if (_needRefreshChunk)
		{
			for (unsigned int i = 0; i < SIGHT * 2 - 1; i++)
				for (unsigned int j = 0; j < SIGHT * 2 - 1; j++)
					for (unsigned int k = 0; k < 16; k++)
					{
						chunk* newChunk = _playerLocation.getWorld()->getChunk((int32_t)_playerLocation.getChunkX() + SIGHT - i - 1, k, (int32_t)_playerLocation.getChunkZ() + SIGHT - j - 1);

						if (!_isChunkInLastSight(newChunk->getChunkX(), newChunk->getChunkZ()) || _needRefreshAllRenderData)
							_newChunkList.push_back(newChunk);
					}
		}
		else
			return;

		_needRefreshAllRenderData = false;
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