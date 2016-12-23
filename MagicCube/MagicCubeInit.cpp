
#include "MagicCube.h"
#include "GameScene.h"

void magiccube_application::init()
{
	//init screen
	for (unsigned int i = 0; i < SCENE_NULL; i++)
	{
		scenes[i] = addScene(new game_scene());
	}
	bindFPC(&FPC);

	showScene(scenes[SCENE_GAME]);
}
void magiccube_application::initResources()
{
	loadExtension(new canvas_extension());
	loadExtension(new normal_shader_extension());
	loadExtension(new fpc_extension());

	textures[TEXTURE_BLOCK] = genTexture({ "BlockTexture.png" }, 1);
}