
#include "../GSRenderEngine.h"

enum scene_name
{
	SCENE_INIT, SCENE_CHOOSE_GAME, SCENE_NULL
};
enum texture_name
{
	TEXTURE_BLOCK, TEXTURE_INIT, TEXTURE_NULL
};
class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	test_app() :application(u8"Test", "1.0.0", size_vec(880,495)) {}

	scene* scenes[SCENE_NULL];

	texture textures[TEXTURE_NULL];

	void init()
	{
		//init screen
		for (unsigned int i = 0; i < SCENE_NULL; i++)
		{
			scenes[i] = addScene();
		}
		//init texture
		char* blockTextureFileName[]{ "block.png","normal.png" };
		char* initTextureFileName[]{ "logo.png" };

		textures[TEXTURE_INIT] = genTexture(initTextureFileName, 1);
		textures[TEXTURE_BLOCK] = genTexture(blockTextureFileName,2);

		scene* initScreen = scenes[SCENE_INIT];

		canvas* logoCanvas = scenes[SCENE_INIT]->addCanvas(gl_manager::getInstance().normal2DShader);

		logoCanvas->addShape(canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(1.0f, -1.0f, 0.0f), texture_pos(1.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(0.0f, 0.0f))
		));

		logoCanvas->addShape(canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(0.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-1.0f, 1.0f, 0.0f), texture_pos(0.0f, 1.0f))
		));

		logoCanvas->bindTexture(textures[TEXTURE_INIT]);

		showScene(initScreen);
	}
	void tickCall()
	{
		count++;

		if (count % 100 == 0)
		{
			std::cout << count / 100 << std::endl;
		}
	}
};
int main()
{
	test_app Test;
	Test.run();
}