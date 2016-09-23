
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
		canvas* testcanvas = testScene->addCanvas();

		canvas_shape canvasShape = testcanvas->addShape(canvas_shape_info
		(
			canvas_point_info(color(0.0f, 1.0f, 0.0f), location<GLfloat>(-0.9f, -0.9f, 0.0f), texture_pos(0.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(0.9f, -0.9f, 0.0f), texture_pos(0.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(0.9f, 0.9f, 0.0f), texture_pos(0.0f, 0.0f))
		));

		showScene(testScene);
	}
	void tickCall()
	{
		count++;

		if (count % 100 == 0)
			std::cout << count / 100 << std::endl;
	}
};
int main()
{
	test_app Test;
	Test.run();
}