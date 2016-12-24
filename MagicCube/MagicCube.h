#pragma once

#include "../GSRenderEngine.h"
#include "../RenderEngine/CanvasExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "GamePlayer.h"
#include "../RenderEngine/ChunkRenderExtension.h"

enum scene_name
{
	SCENE_GAME, SCENE_NULL
};
enum texture_name
{
	TEXTURE_BLOCK, TEXTURE_NULL
};

class magiccube_application :public application
{
private:
	unsigned long int count = 0;

public:
	magiccube_application() :application(u8"MagicCube", "0.0.0", size_vec(880, 495)) {}

	scene_node* scenes[SCENE_NULL];
	texture* textures[TEXTURE_NULL];

	void initResources();
	void init();
};