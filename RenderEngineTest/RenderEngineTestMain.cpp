
#include "../GSRenderEngine.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "../RenderEngine/FPCExtension.h"
#include "../RenderEngine/ModLoader.h"
#include "../RenderEngine/CanvasExtension.h"
#include "../RenderEngine/NormalShader.h"

texture* logoTexture;
texture* blockTexture;
scene_node* firstScene;

canvas* logo;

class testListener:public listener
{
	int ID;
	unsigned int tick = 0;

public:
	testListener(int ID) :ID(ID) {}

	~testListener()
	{
		std::cout << "Listener: " << ID << "has been unregister" << std::endl;
	}
	void tickListener()
	{
		tick++;

		if (tick % 50 == 0)
		{
			std::cout << (1 - tick) * 10.0f << "%" << std::endl;

			//chunk_render* chunkRendere = (chunk_render*)firstScene->addRenderNode(new chunk_render(10));

			//chunkRendere->bindTexture(blockTexture);

			//chunkRendere->getModelLocation()->getLocation()->setY(tick / 50);
		}
		else if (tick == 2)
			std::cout << "now there are more than 2 rendernode,they had been added in 10 seconds" << std::endl;
	}
	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_Q)
			application::getInstance().unregisterListener(this);

		if (ID == 0)
			std::cout << "[Listener: " << ID << "]" << key << std::endl;
		else if (ID == 1)
		{
			std::cout << "[Listener: " << ID << "]" << action << std::endl;
		}
	}
};
class test_app :public application
{
public:
	canvas* coordinateX;
	canvas* coordinateZ;

	chunk_render* testRenderNode;

	fpc fpController = fpc(getGlobalCamera());

	test_app() :application(u8"MagicCube-RenderEngineTest gs test", "test-1.0.0", size_vec(880, 495)) {}

	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			if (isCursorEnable.load())
			{
				//bind fpc
				bindFPC(&fpController);
			}
			else
			{
				//bind fpc
				bindFPC(nullptr);
			}
	}

	void initResources()
	{
		loadExtension(new normal_shader_extension());
		loadExtension(new canvas_extension());
		loadExtension(new chunk_render_extension());
		
		logoTexture = genTexture({ "Logo.png" }, 1);
		blockTexture = genTexture({ "BlockTexture.png", "BlockTextureNormal.png" }, 2);

		glClearColor(0.1, 0.4, 0.6, 0.0);
	}
	void init()
	{
		bindFPC(&fpController);

		firstScene = addScene();
		
		logo = (canvas*)firstScene->addRenderNode(new canvas(normal3DRenderProgram));

		logo->addShapes(new canvas_shape[2]
		{
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, -1.0f), texture_pos(1.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, 1.0f, -1.0f), texture_pos(0.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, -1.0f), texture_pos(0.0f, 1.0f))
			)
			,
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, -1.0f), texture_pos(0.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, -1.0f, -1.0f), texture_pos(1.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, -1.0f), texture_pos(1.0f, 0.0f))
			)
		}, 2);
		
		firstScene->addRenderNode(new chunk_render(10))->bindTexture(blockTexture);

		logo->bindTexture(logoTexture);

		showScene(firstScene);

		registerListener(new testListener(1));
	}
	unsigned int tick = 0;

	void tickListener()
	{
		tick++;

		if (tick % 50 == 0)
			std::cout << tick / 50 << std::endl;

	}
};

test_app Test;

int main()
{
	Test.run();
}