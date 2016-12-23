#pragma once

#include "../WorldManager.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../GSRenderEngine.h"

class game_world_manager :public world_manager, input_callback
{
private:
	std::vector<chunk_render*> _chunkRenderList;

	scene_node* _scene;

public:
	game_world_manager(scene_node* scene)
	{
		_scene = scene;
	}
};