
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

chunk_render* testRenderNode;

class testListener:public input_callback
{
	int ID;
	unsigned int tick = 0;

public:
	testListener(int ID) :ID(ID) {}

	void tickListener()
	{
		tick++;

		if (tick % 50 == 0)
		{
			//chunk_render* newChunkRender = (chunk_render*)firstScene->addRenderNode(new chunk_render(10));

			//unsigned int newChunkLocation = tick / 50;

			//newChunkRender->bindTexture(blockTexture);
			//newChunkRender->getModelLocation()->getLocation()->move((newChunkLocation / 16) * 16, 0, (newChunkLocation - (newChunkLocation / 16) * 16) * 16);

			//std::cout << "add new chunk " << tick % 50 << "at:" << (newChunkLocation % 16) * 16 << "," << (newChunkLocation - (newChunkLocation / 16) * 16) * 16 << std::endl;
		}

		//application::getInstance().getGlobalCamera()->getLocation()->moveTo(application::getInstance().getGlobalCamera()->getLocation()->getX(), 17, application::getInstance().getGlobalCamera()->getLocation()->getZ());

		auto PlayerLocation = application::getInstance().getGlobalCamera()->getLocation();

		testRenderNode->setLight(0.5f, cos(tick / 100.0), sin(tick / 100.0));

		logo->getModelLocation()->getLocation()->moveTo(0.5f, cos(tick / 100.0), sin(tick / 100.0));
	}
	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_Q)
			application::getInstance().unregisterInputCallback(this);

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

	fpc fpController = fpc(getGlobalCamera());

	test_app() :application(u8"MagicCube-RenderEngineTest gs test", "test-1.0.0", size_vec(880, 495)) {}

	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			if (isCursorEnableSynch.load())
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

		glClearColor(0.1f, 0.4f, 0.6f, 0.0f);
	}
	void init()
	{
		getGlobalCamera()->getLocation()->moveTo(2.0, 0.0, -1.0);

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
		
		testRenderNode = (chunk_render*)firstScene->addRenderNode(new chunk_render(10));
		testRenderNode->bindTexture(blockTexture);

		logo->bindTexture(logoTexture);

		showScene(firstScene);

		registerInputCallback(new testListener(1));
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