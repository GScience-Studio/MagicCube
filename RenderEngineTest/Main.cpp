
#include "../GSRenderEngine.h"
#include "../RenderEngine/MapRenderExtension.h"
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
	void init()
	{
		//load extension
		loadExtension(new map_render_extension());
		loadExtension(new fpc_extension());
		loadExtension(new normal_shader_extension());
		loadExtension(new canvas_extension());
	
		//bind fpc
		bindFPC(&fpController);

		//add test render node
		scene* firstScene = addScene();

		render_node* testRenderNode = firstScene->addRenderNode(new map_render(10));

		testRenderNode->bindTexture(genTexture({ "BlockTexture.png" }, 1));

		//add coordinate
		canvas* coordinate = (canvas*)firstScene->addRenderNode(new canvas(normal2DShader));

		coordinate->addShapes(new canvas_shape[2]
		{
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(0.1f, 0.1f, 0.0f), texture_pos(1.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-0.1f, 0.1f, 0.0f), texture_pos(0.0f, 0.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-0.1f, -0.1f, 0.0f), texture_pos(0.0f, 1.0f))
			)
			,
			canvas_shape
			(
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-0.1f, -0.1f, 0.0f), texture_pos(0.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(0.1f, -0.1f, 0.0f), texture_pos(1.0f, 1.0f)),
				canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(0.1f, 0.1f, 0.0f), texture_pos(1.0f, 0.0f))
			)
		}, 2);

		coordinate->bindTexture(genTexture({ "Coordinate.png" }, 1));

		showScene(firstScene);

		//clear color
		glClearColor(0.0f, 0.5f, 0.7f, 0.0f);

	}
	void tickCall()
	{
		
	}
};
test_app Test;

int main()
{
	Test.run();
}