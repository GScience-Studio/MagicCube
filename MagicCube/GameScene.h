#pragma once

#include "MagicCube.h"
#include "GameWorldManager.h"

class game_scene :public scene_node, input_callback, game_world_manager
{
public:
	game_scene() :game_world_manager(this)
	{
		application::getInstance().registerInputCallback(this);
	}
	void tickListener()
	{
		refreshWorld();
	}
};