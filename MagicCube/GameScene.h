#pragma once

#include "MagicCube.h"
#include "GameWorldManager.h"

class game_scene :public scene_node, input_callback, game_world_manager
{
private:
	world* _mainWorld = loadWorld("MainWorld");

	game_player _gamePlayer;

public:
	game_scene(texture* texture) :game_world_manager(this, texture), _gamePlayer(this) {}

	void onUnload()
	{
		bindFPC(nullptr);

		application::getInstance().unregisterInputCallback(this);
	}
	void onLoad()
	{
		bindFPC(&_gamePlayer);

		application::getInstance().registerInputCallback(this);

		world* MainWorld = loadWorld("MainWorld");

		_gamePlayer.setPlayerWorld(MainWorld);
		_gamePlayer.getCamera()->getLocation()->moveTo(0, 100, 0);
		_gamePlayer.getCamera()->getAngle()->setPosX(-0.5f);
	}
	void tickListener()
	{
		refreshGameWorld();
	}
};