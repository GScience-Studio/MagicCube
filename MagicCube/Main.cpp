
#include "../GSRenderEngine.h"

class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	test_app() :application(u8"Test", "1.0.0", size_vec(500,600)) {}

	canvas* testcanvas;

	void init()
	{
		scene* testScene = addScene();

		testcanvas = testScene->addCanvas();

		showScene(testScene);
	}
	void tickCall()
	{
		count++;

		if (count % 100 == 0 && count < 5000)
		{
			testcanvas->clear();

			for (int i = -50; i<50; i++)
				for (int j = -50; j<50; j++)
					for (int k = -50; k<50; k++)
						testcanvas->addShape(canvas_shape
						(
							canvas_point_info(color(count / 100 % 2 == 0 ? 1.0f : 0.0f, 0.0f, 0.0f), location<GLfloat>(i * 0.01f + 0.01f, j * 0.01f + 0.01f, k * 0.01f), texture_pos(0.0f, 0.0f)),
							canvas_point_info(color(count / 100 % 2 == 0 ? 1.0f : 0.0f, 0.0f, 0.0f), location<GLfloat>(i * 0.01f, j * 0.01f + 0.01f, k * 0.01f), texture_pos(0.0f, 0.0f)),
							canvas_point_info(color(count / 100 % 2 == 0 ? 1.0f : 0.0f, 0.0f, 0.0f), location<GLfloat>(i * 0.01f + 0.01f, j * 0.01f, k * 0.01f), texture_pos(0.0f, 0.0f))
						));
		}
		if (count % 100 == 0)
		{
			std::cout << count / 100 << std::endl;
		}
	}
};
int main()
{
	test_app Test;
	Test.run();
}