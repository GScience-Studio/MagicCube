
#include "../GSRenderEngine.h"
#include "../RenderEngine/CanvasExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "../RenderEngine/FPCExtension.h"

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

	fpc	FPC = fpc(getGlobalCamera());

	scene_node* scenes[SCENE_NULL];
	texture* textures[TEXTURE_NULL];

	void initResources()
	{
		loadExtension(new canvas_extension());
		loadExtension(new normal_shader_extension());
		loadExtension(new fpc_extension());

		textures[TEXTURE_INIT] = genTexture({ "logo.png" }, 1);
		textures[TEXTURE_BLOCK] = genTexture({ "BlockTexture.png" }, 1);
	}
	void init()
	{
		bindFPC(&FPC);

		//init screen
		for (unsigned int i = 0; i < SCENE_NULL; i++)
		{
			scenes[i] = addScene();
		}

		scene_node* initScreen = scenes[SCENE_INIT];

		canvas* logoCanvas = (canvas*)scenes[SCENE_INIT]->addRenderNode(new canvas(normal3DRenderProgram));

		logoCanvas->addShapes(&canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(0.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(1.0f, -1.0f, 0.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(1.0f, 0.0f))
		), 1);

		logoCanvas->addShapes(&canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(0.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(1.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), render_location<GLfloat>(-1.0f, 1.0f, 0.0f), texture_pos(0.0f, 0.0f))
		), 1);

		logoCanvas->bindTexture(textures[TEXTURE_INIT]);

		showScene(initScreen);
	}
	void tickCall()
	{
		count++;

		if (count >= 500)
		{
			showScene(scenes[SCENE_CHOOSE_GAME]);
		}
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