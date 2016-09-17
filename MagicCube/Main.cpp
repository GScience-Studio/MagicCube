
#include "../GSRenderEngine.h"

class test_app :public application
{
public:
	test_app() :application(u8"Test", "1.0.0", size_vec(100,10)) {}

	void _init()
	{
		scene* initScene = addScene();
		initScene->addRenderNode(canvas());
		scene* initScene2 = addScene();

		initScene2->addRenderNode(canvas());
		canvas testcanvas = initScene2->addCanvas();

		showScene(initScene2);
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