
#include "../GSRenderEngine.h"

class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	test_app() :application(u8"Test", "1.0.0", size_vec(500,600)) {}

	void init()
	{
		scene* testScene = addScene();

		testScene->addRenderNode(canvas());
		canvas testcanvas = testScene->addCanvas();

		showScene(testScene);
	}
	void tickCall()
	{
		count++;

		if (count / 60 == count / 60.0f)
			std::cout << (count / 60) + 1 << std::endl;
	}
};
int main()
{
	test_app Test;
	Test.run();
}