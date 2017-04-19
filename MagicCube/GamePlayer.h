#pragma once

#include "../RenderEngine/FPCExtension.h"
#include "GameWorldManager.h"

class game_player :public fpc
{
private:
	game_world_manager* _gameWorldManager;
	world* _playerWorld;

public:
	game_player(game_world_manager* gameWorldManager):fpc(application::getInstance().getGlobalCamera())
	{
		_fpcSpeed = 20;

		_gameWorldManager = gameWorldManager;
	}
	
	world* getWorld()
	{
		return _playerWorld;
	}
	void setPlayerWorld(world* world)
	{
		_playerWorld = world;
	}
	void onMove(double x, double y, double z, double posX, double posY)
	{
		_gameWorldManager->transport(_playerWorld, x, y, z);
	}
};