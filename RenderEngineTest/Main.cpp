
#include "../GSRenderEngine.h"
#include "../RenderEngine/ShapeCube.h"

class test_app :public application
{
private:
	unsigned long int count = 0;

public:
	test_app() :application(u8"Test", "1.0.0", size_vec(880, 495)) {}

	void init()
	{
		//init screen
		scene* testScene = addScene();

		//init texture
		char* blockTextureFileName[]{ "block.png","normal.png" };

		texture texture = genTexture(blockTextureFileName, 2);

		canvas* logoCanvas = testScene->addCanvas(normal2DShader);

		logoCanvas->addShapes(
			shape_cube(cube_texture(
		vec<texture_pos, 4>{ texture_pos{ 1.0,0.0 } ,texture_pos{ 1.0,0.0 } ,texture_pos{ 1.0,0.0 } ,texture_pos{ 1.0,0.0 } }
		, vec<color, 4>{ color( 0.0,0.0,0.0 ), color( 0.0,0.0,0.0 ), color( 0.0,0.0,0.0 ), color( 0.0,0.0,0.0 ) })
		, 1, camera(0.0, 0.0, -1.0, 0.0f, 0.0f)),2
		);

		logoCanvas->bindTexture(texture);

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