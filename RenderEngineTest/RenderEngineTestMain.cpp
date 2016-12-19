
#include "../GSRenderEngine.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../RenderEngine/FPCExtension.h"

#define SIGHT 16

class test_app :public application
{
private:
	unsigned int _tick;

public:
	fpc fpController = fpc(getGlobalCamera());

	texture*	blockTexture;
	scene_node* firstScene;

	test_app() :application(u8"MagicCube-RenderEngineTest render test", "test-1.0.0", size_vec(880, 495)) {}

	void keyListener(int key, int action)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
			if (isCursorEnableSynch.load())
			{
				//bind fpc
				bindFPC(&fpController);
			}
			else
			{
				//bind fpc
				bindFPC(nullptr);
			}
	}

	void tickListener()
	{
		_tick++;
		/*
		if (_tick % 5 != 0)
			return;

		if (_tick % 50 == 0)
			std::cout << "add a new chunk,now there are " << _tick / 5 << "chunks," << 2032 * _tick / 5 << " blocks," << 2032 * _tick / 5 * 6 << "cubes." << std::endl;
		
		blockRenderData* testBlockRenderDataList = new blockRenderData[4096];

		chunk_render* testRenderNode = (chunk_render*)firstScene->addRenderNode(new chunk_render(testBlockRenderDataList));

		testRenderNode->getModelCamera()->getLocation()->moveTo(((_tick / 5u) << 20 >> 28) * 16, ((_tick / 5u) << 24 >> 24) * 16, ((_tick / 5u) << 16 >> 28) * 16);

		testRenderNode->bindTexture(blockTexture);

		delete[](testBlockRenderDataList);
		*/
	}
	void initResources()
	{
		loadExtension(new chunk_render_extension());

		blockTexture = genTexture({ "BlockTexture.png"}, 1);

		glClearColor(0.1f, 0.4f, 0.6f, 0.0f);
	}
	void init()
	{
		bindFPC(&fpController);

		firstScene = addScene();

		showScene(firstScene);

		//load chunks
		
		chunk_render* chunk[SIGHT * SIGHT * 4];

		double startTime = glfwGetTime();

		for (int i = 0; i < SIGHT * 2; i++)
			for (int j = 0; j < SIGHT * 2; j++)
				for (int k = 0; k < 1; k++)
				{
					chunk[i + SIGHT * 2 * j] = new chunk_render(firstScene, blockTexture);

					chunk[i + SIGHT * 2 * j]->setChunkLocation(i, k, j);

					blockRenderData testBlockDatas[4096];

					for (unsigned short i2 = 0; i2 < 16; i2++)
					{
						for (unsigned short j2 = 0; j2 < 16; j2++)
						{
							testBlockDatas[i2 + j2 * 16].setBlockRenderData(blockChunkLocationToShort(i2, 4, j2), 32);
							testBlockDatas[i2 + j2 * 16].setNearbyBlockAlpha(true, true, false, false, false, false);
							testBlockDatas[i2 + j2 * 16].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
							testBlockDatas[i2 + j2 * 16].setAlpha(true);
						}
					}
					for (unsigned short i2 = 0; i2 < 16; i2++)
					{
						for (unsigned short j2 = 0; j2 < 16; j2++)
						{
							testBlockDatas[i2 + j2 * 16 + 256].setBlockRenderData(blockChunkLocationToShort(i2, 0, j2), 0);
							testBlockDatas[i2 + j2 * 16 + 256].setNearbyBlockAlpha(true, true, false, false, false, false);
							testBlockDatas[i2 + j2 * 16 + 256].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
						}
					}

					testBlockDatas[512].setBlockRenderData(blockChunkLocationToShort(0, 10, 0), 1);
					testBlockDatas[512].setNearbyBlockAlpha(true, true, true, true, true, true);
					testBlockDatas[512].setNearbyBlockLight(15, 15, 15, 15, 15, 15);

					testBlockDatas[513].setBlockRenderData(blockChunkLocationToShort(10, 10, 10), 0);
					testBlockDatas[513].setNearbyBlockAlpha(false, false, false, false, false, false);

					chunk[i + SIGHT * 2 * j]->setBlockRenderDatas(testBlockDatas, 4096);
				}

		double finishTime = glfwGetTime();

		std::cout << "add " << SIGHT * SIGHT * 2 << " chunks use " << finishTime - startTime << "s" << std::endl;

		fpController.getCamera()->getLocation()->moveTo(SIGHT * 16, 10, SIGHT * 16);
	}
};

test_app Test;

int main()
{
	Test.run();
}