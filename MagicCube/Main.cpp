
#include "../GSRenderEngine.h"

class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	test_app() :application(u8"Test", "1.0.0", size_vec(600,600)) {}

	canvas* testcanvas1;
	canvas* testcanvas2;

	void init()
	{
		scene* testScene = addScene();

		testcanvas1 = testScene->addCanvas();
		testcanvas2 = testScene->addCanvas();

		char* textureFileName[]{ "block.png","normal.png"};

		texture blockTexture = genTexture(textureFileName,2);

		testcanvas1->addShape(canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-0.9f, -0.9f, 0.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(0.9f, -0.9f, 0.0f), texture_pos(1.0f, 0.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(0.9f, 0.9f, 0.0f), texture_pos(0.0f, 0.0f))
		));

		testcanvas2->addShape(canvas_shape
		(
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-0.9f, -0.9f, 0.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(0.9f, 0.9f, 0.0f), texture_pos(0.0f, 0.0f)), 
			canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-0.9f, 0.9f, 0.0f), texture_pos(0.0f, 1.0f))
		));

		testcanvas1->bindTexture(blockTexture);
		testcanvas2->bindTexture(blockTexture);

		showScene(testScene);
	}
	void tickCall()
	{
		count++;

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