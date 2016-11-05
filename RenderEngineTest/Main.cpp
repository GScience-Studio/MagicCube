
#include "../GSRenderEngine.h"
#include "../RenderEngine/CanvasExtension.h"
#include "../RenderEngine/NormalShaderExtension.h"
#include "../RenderEngine/FPCExtension.h"
#include "../RenderEngine/ModLoader.h"

canvas* logoCanvas;
canvas* coordinateCanvas2;

listener* listener1;
listener* listener2;

unsigned long int count = 0;

class test_scene:public scene
{
	void sceneTickCall() 
	{
		logoCanvas->getModelLocation()->getAngle()->setPosY(logoCanvas->getModelLocation()->getAngle()->getPosY() + 0.1f);
		//coordinateCanvas2->getNodeCamera()->getAngle()->setPosY(logoCanvas->getNodeCamera()->getAngle()->getPosY() + 0.1f);
		/*
		coordinateCanvas2->addShapes(new canvas_shape[2]
		{ 
		canvas_shape
		(
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, count / 1000.0f), texture_pos(1.0f, 0.0f)),
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, 1.0f, count / 1000.0f), texture_pos(0.0f, 0.0f)),
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, count / 1000.0f), texture_pos(0.0f, 1.0f))
		)
		,
		canvas_shape
		(
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(-1.0f, -1.0f, count / 1000.0f), texture_pos(0.0f, 1.0f)),
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, -1.0f, count / 1000.0f), texture_pos(1.0f, 1.0f)),
			canvas_point_info(color(0.0, 0.0, 0.0), location<GLfloat>(1.0f, 1.0f, count / 1000.0f), texture_pos(1.0f, 0.0f))
		)
		}, 2);*/
	}
};
class testListener:public listener
{
	int ID;
public:
	testListener(int ID) :ID(ID) {}

	~testListener()
	{
		std::cout << "Listener: " << ID << "has been unregister" << std::endl;
	}
	virtual void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_Q)
			application::getInstance().unregisterListener(this);

		if (ID == 0)
			std::cout << "[Listener: " << ID << "]" << key << std::endl;
		else if (ID == 1)
		{
			std::cout << "[Listener: " << ID << "]" << action << std::endl;
		}
	}
};
class test_app :public application
{
public:
	fpc fpController = fpc(getGlobalCamera());

	test_app() :application(u8"MagicCube-RenderEngineTest", "beta-1.0.0", size_vec(880, 495)) {}

	void init()
	{
		std::vector<double> modle = loadOBJ("testModle.obj");

		//load extension
		loadExtension(new normal_shader_extension());
		loadExtension(new fpc_extension());

		//init screen
		scene* testScene = addScene(new test_scene());
		
		//init texture
		char* coordinateTextureFileName[]{ "coordinate.png","normal.png" };
		texture coordinateTexture = genTexture(coordinateTextureFileName, 2);

		char* coordinateTextureFileName3[]{ "testModleTexture.png" };
		texture coordinateTexture3 = genTexture(coordinateTextureFileName3, 1);

		char* blockTextureFileName[]{ "logo.png","normal.png" };
		texture logoTexture = genTexture(blockTextureFileName, 2);

		//add canvas(render node)
		canvas* coordinateCanvas = (canvas*)testScene->addRenderNode(new canvas(normal3DShader));
		coordinateCanvas2 = (canvas*)testScene->addRenderNode(new canvas(normal3DShader));

		//add shape
		shape_cube testCube(cube_texture(
			vec<texture_pos, 4>{ texture_pos{ 0.0,0.0 }, texture_pos{ 0.0,1.0 }, texture_pos{ 1.0,1.0 }, texture_pos{ 1.0,0.0 } }
		, vec<color, 4>{ color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0) })
			, 1);
		coordinateCanvas->addShapes(testCube, 2);

		coordinateCanvas2->addShapes(&modle[0], modle.size());
		coordinateCanvas2->getModelLocation()->getLocation()->setZ(5.0);
		coordinateCanvas2->getModelLocation()->getLocation()->setY(-5.0);

		logoCanvas = (canvas*)testScene->addRenderNode(new canvas(normal3DShader));

		//add shape
		shape_cube testCube2(cube_texture(
			vec<texture_pos, 4>{ texture_pos{ 0.0,0.0 }, texture_pos{ 0.0,1.0 }, texture_pos{ 1.0,1.0 }, texture_pos{ 1.0,0.0 } }
		, vec<color, 4>{ color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0), color(0.0, 0.0, 0.0) })
			, 1);
		logoCanvas->addShapes(testCube2, 2);
		
		//bind texture
		coordinateCanvas->bindTexture(coordinateTexture3);
		logoCanvas->bindTexture(logoTexture);
		coordinateCanvas2->bindTexture(coordinateTexture3);

		coordinateCanvas->getNodeCamera()->getLocation()->setZ(-3.0);
		logoCanvas->getModelLocation()->getLocation()->setZ(5.0);
		logoCanvas->getModelLocation()->getLocation()->setY(0.0);
		logoCanvas->getModelLocation()->getLocation()->setX(0.0);

		logoCanvas->getModelLocation()->getAngle()->setPosY(3.14f / 4.0f);

		bindFPC(&fpController);

		//show screen
		showScene(testScene);

		//register listener
		listener1 = registerListener(new testListener(0));
		listener2 = registerListener(new testListener(1));
	
	}
	void tickCall()
	{
		count++;

		if (count % 50 == 0)
		{
			std::cout << "now has "<< count << " cube in a scene" << std::endl;

			if (count / 50 > 5)
				application::getInstance().unregisterListener(listener1);
			if (count / 50 > 10)
				application::getInstance().unregisterListener(listener2);
		}
	}
};
test_app Test;

int main()
{
	Test.run();
}