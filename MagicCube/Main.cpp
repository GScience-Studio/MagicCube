
#include "../GSRenderEngine.h"

class test_app :public application
{
public:
	test_app() :application(u8"Test", "1.0.0",size(100,10)) {}

	void init()
	{

	}
	void tickCall()
	{

	}
};
int main()
{
	test_app Test;
	Test.run();
}