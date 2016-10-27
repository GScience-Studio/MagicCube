
#include "../GSRenderEngine.h"
#include "../RenderEngine/ShapeCube.h"
#include "../RenderEngine/NormalShader.h"

class test_scene:public scene
{
	void sceneTickCall() 
	{
		std::cout << "³¡¾°Tick²âÊÔ" << std::endl;
	}
};
class test_app :public application
{
private:
	unsigned long int count = 0;

public:
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
		canvas* logoCanvas = (canvas*)testScene->addRenderNode(new canvas(normal2DShader));

		//add shape
		shape_cube testCube(cube_texture(
			vec<texture_pos, 4>{ texture_pos{ 0.0,0.0 }, texture_pos{ 0.0,1.0 }, texture_pos{ 1.0,1.0 }, texture_pos{ 1.0,0.0 } }
		, vec<color, 4>{ color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0) })
			, 1);
		logoCanvas->addShapes(testCube, 2);
		
		//bind texture
		logoCanvas->bindTexture(texture);

		//show screen
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