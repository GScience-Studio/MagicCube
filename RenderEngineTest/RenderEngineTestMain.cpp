
#include "../GSRenderEngine.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "../RenderEngine/FPCExtension.h"
#include "../RenderEngine/ModLoader.h"
#include "../RenderEngine/CanvasExtension.h"
#include "../RenderEngine/NormalShader.h"

class testListener:public listener
{
	int ID;
public:
	testListener(int ID) :ID(ID) {}

	~testListener()
	{
		std::cout << "Listener: " << ID << "has been unregister" << std::endl;
	}
	virtual void keyListener(int key, int action)
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
	canvas* logo;

	chunk_render* testRenderNode;

	fpc fpController = fpc(getGlobalCamera());

	test_app() :application(u8"MagicCube-RenderEngineTest gs test", "test-1.0.0", size_vec(880, 495)) {}

	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			if (isCursorEnable)
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
	texture logoTexture;

	void initResources()
	{
		loadExtension(new normal_shader_extension());
		loadExtension(new canvas_extension());

		logoTexture = genTexture({ "Logo.png" }, 1);
	}
	void init()
	{
		scene_node* firstScene = addScene();

		logo = (canvas*)firstScene->addRenderNode(new canvas(normal3DShader));

		logo->addShapes(new canvas_shape[2]
		{
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(1.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, 1.0f, 0.0f), texture_pos(0.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(0.0f, 1.0f))
			)
			,
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(0.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, -1.0f, 0.0f), texture_pos(1.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(1.0f, 0.0f))
			)
		}, 2);

		logo->bindTexture(logoTexture);

		showScene(firstScene);
	}
	unsigned int tick = 0;

	void tickListener()
	{
		tick++;

		float angle = tick * PI / 180;

		logo->getModelLocation()->getAngle()->setPosY(-angle + 180);

	}
};
test_app Test;

int main()
{
	Test.run();
}