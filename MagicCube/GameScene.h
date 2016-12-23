#pragma once

#include "MagicCube.h"
#include "GameWorldManager.h"

class init_scene :public scene_node, input_callback, game_world_manager
{
public:
	init_scene() :game_world_manager(this)
	{
		application::getInstance().registerInputCallback(this);
	}
	void tickListener()
	{
		refreshWorld();
	}
};