
#include "../GSRenderEngine.h"
#include "../RenderEngine/ShapeCube.h"
#include "../RenderEngine/NormalShader.h"
#include "../RenderEngine/FPSController.h"

void keyDown(int key, int action);

class test_scene:public scene
{
	void sceneTickCall() 
	{
		
	}
};
class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	fps_controller fpsController = fps_controller(getGlobalCamera());

	test_app() :application(u8"MagicCube-RenderEngineTest", "beta-1.0.0", size_vec(880, 495)) {}

	void init()
	{
		//init screen
		scene* testScene = addScene(new test_scene());

		//init texture
		char* blockTextureFileName[]{ "block.png","normal.png" };
		texture texture = genTexture(blockTextureFileName, 2);

		initNormalShadersExtension();

		//add canvas(render node)
		canvas* logoCanvas = (canvas*)testScene->addRenderNode(new canvas(normal3DShader));

		//add shape
		shape_cube testCube(cube_texture(
			vec<texture_pos, 4>{ texture_pos{ 0.0,0.0 }, texture_pos{ 0.0,1.0 }, texture_pos{ 1.0,1.0 }, texture_pos{ 1.0,0.0 } }
		, vec<color, 4>{ color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0) })
			, 1);
		logoCanvas->addShapes(testCube, 2);
		
		//bind texture
		logoCanvas->bindTexture(texture);

		logoCanvas->getModelLocation()->getLocation()->setZ(10.0);
		logoCanvas->getModelLocation()->getLocation()->setY(-5.0);
		logoCanvas->getModelLocation()->getLocation()->setX(3.0);

		//show screen
		showScene(testScene);

		//register listener
		registerListener(keyDown);
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
test_app Test;

int main()
{
	Test.run();
}
void keyDown(int key, int action)
{
	Test.fpsController.refresh(key, action);
}