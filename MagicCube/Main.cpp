
#include "../GSRenderEngine.h"

class test_app :public application
{
public:
	test_app() :application(u8"Test", "1.0.0", size_vec(100,10)) {}

	void _init()
	{
		screen initScreen = addScreen();

		addCanvas(initScreen);
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