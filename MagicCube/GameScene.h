#pragma once

#include "MagicCube.h"
#include "GameWorldManager.h"

class game_scene :public scene_node, input_callback, game_world_manager
{
private:
	world* _mainWorld = loadWorld("MainWorld");

	game_player _gamePlayer;

public:
	game_scene(texture* texture) :game_world_manager(this, texture), _gamePlayer(this)
	{
		application::getInstance().registerInputCallback(this);

		world* MainWorld = loadWorld("MainWorld");

		transport(_mainWorld, 0, 0, 0);

		bindFPC(&_gamePlayer);
	}
	void tickListener()
	{
		refreshGameWorld();
	}
};