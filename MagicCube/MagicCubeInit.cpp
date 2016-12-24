
#include "MagicCube.h"
#include "GameScene.h"

void magiccube_application::init()
{
	//init screen
	for (unsigned int i = 0; i < SCENE_NULL; i++)
	{
		scenes[i] = addScene(new game_scene(textures[TEXTURE_BLOCK]));
	}
	showScene(scenes[SCENE_GAME]);
}
void magiccube_application::initResources()
{
	loadExtension(new canvas_extension());
	loadExtension(new normal_shader_extension());
	loadExtension(new chunk_render_extension());
	loadExtension(new fpc_extension());

	textures[TEXTURE_BLOCK] = genTexture({ "BlockTexture.png" }, 1);

	glClearColor(0.0, 0.3, 0.6, 0.0);
}