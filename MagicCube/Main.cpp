
#include "../GSRenderEngine.h"

class test_app :public application
{
public:
	test_app() :application(u8"Test", "1.0.0", size_vec(500,600)) {}

	void _init()
	{
		scene* testScene = addScene();

		testScene->addRenderNode(canvas());
		canvas testcanvas = testScene->addCanvas();

		showScene(testScene);
	}
	void _tickCall()
	{

	}
};
int main()
{
	test_app Test;
	Test.run();
}