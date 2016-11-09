
#include "../GSRenderEngine.h"
#include "../RenderEngine/MapRenderExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "../RenderEngine/FPCExtension.h"
#include "../RenderEngine/ModLoader.h"

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

	test_app() :application(u8"MagicCube-RenderEngineTest", "beta-1.0.0", size_vec(880, 495)) {}

	void init()
	{
		//load extension
		loadExtension(new map_render_extension());
		loadExtension(new fpc_extension());
	
		//bind fpc
		bindFPC(&fpController);

		scene* firstScene = addScene();

		firstScene->addRenderNode(new map_render(10))->getModelLocation()->getLocation()->moveTo(0.0,0.0,10.0);
		showScene(firstScene);

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