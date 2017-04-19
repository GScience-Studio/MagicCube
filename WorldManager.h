#pragma once

#define SIGHT 16
#define MAX_CHUNK_TASK_IN_ONE_TICK 32

#include "WorldManager\World.h"
#include "WorldManager\Location.h"
#include <vector>
#include <string.h>

class world_manager
{
protected:
	struct refresh_progress
	{
		int lastChunkX;
		int lastChunkZ;

		unsigned short x;
		unsigned short y;
		unsigned short z;

		refresh_progress(unsigned short x, unsigned short y, unsigned short z, int lastChunkX, int lastChunkZ) :x(x), y(y), z(z), lastChunkX(lastChunkX), lastChunkZ(lastChunkZ) {}
	};

	std::map<std::string, world*> _worldMap;

	std::vector<chunk*> _newChunkList;

	location _playerLocation = location(nullptr, 0, 0, 0);

	int32_t _lastChunkX;
	int32_t _lastChunkZ;

	bool _needRefreshAllChunkData = true;

	bool _isChunkInSight(int chunkX, int chunkZ, int inChunkX, int inChunkZ) const
	{
		return abs(chunkX - inChunkX) < SIGHT &&
			abs(chunkZ - inChunkZ) < SIGHT;
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
		if (_playerLocation.getChunkX() != inLocation.getChunkX() || _playerLocation.getChunkZ() != inLocation.getChunkZ())
		{
			_lastChunkX = _playerLocation.getChunkX();
			_lastChunkZ = _playerLocation.getChunkZ();
		}

		if (inLocation.getWorld() != nullptr)
			_playerLocation = inLocation;
		else
			_playerLocation = location(_playerLocation.getWorld(), inLocation.getX(), inLocation.getY(), inLocation.getZ());
	}

	//return the progress
	void refreshWorld(refresh_progress* progress)
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
		unsigned int chunkTask = 0;
		
		//如果是新一轮循环则记录之前所在Chunk的位置
		if (progress->x == 0 && progress->y == 0 && progress->z == 0)
		{
			//没动的话退出
			if (progress->lastChunkX == _lastChunkX && progress->lastChunkZ == _lastChunkZ && !_needRefreshAllChunkData)
				return;

			progress->lastChunkX = _lastChunkX;
			progress->lastChunkZ = _lastChunkZ;
		}
		//check chunks
		for (progress->x; progress->x < SIGHT; progress->x++)
		{
			for (progress->z; progress->z < SIGHT; progress->z++)
			{
				for (progress->y; progress->y < 16; progress->y++)
				{
					if (chunkTask > MAX_CHUNK_TASK_IN_ONE_TICK && !_needRefreshAllChunkData)
						return;

					for (int l = -1; l < 2; l += 2)
					{
						for (int m = -1; m < 2; m += 2)
						{
							if ((progress->x == 0 && l == 1) || (progress->z == 0 && m == 1))
								break;

							chunk* getChunk = _playerLocation.getWorld()->getChunk((int32_t)_playerLocation.getChunkX() + progress->x * l, progress->y, (int32_t)_playerLocation.getChunkZ() + progress->z * m);

							if (getChunk->isNewChunk())
							{
								getChunk->getWorld()->buildChunk(getChunk);

								_newChunkList.push_back(getChunk);

								chunkTask++;
							}
						}
					}
				}
				progress->y = 0;
			}
			progress->z = 0;
		}

		progress->x = 0;
		progress->y = 0;
		progress->z = 0;

		_needRefreshAllChunkData = false;
	}
	~world_manager()
	{
		for (auto world = _worldMap.begin(); world != _worldMap.end(); world++)
		{
			delete (*world).second;
		}
	}
};