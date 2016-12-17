
#include "../GSRenderEngine.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../RenderEngine/FPCExtension.h"

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
		
		chunk_render* chunk[32 * 32];

		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
				for (int k = 0; k < 2; k++)
				{
					chunk[i + 32 * k] = new chunk_render(firstScene, blockTexture);

					chunk[i + 32 * k]->setChunkLocation(i, k, j);

					blockRenderData testBlockDatas[257];

					if (i == 16 && j == 16)
					{
						testBlockDatas[0].setBlockRenderData(blockChunkLocationToShort(0, 4, 0), 32);
						testBlockDatas[0].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
						testBlockDatas[0].setAlpha(true);

						chunk[i + 32 * k]->setBlockRenderDatas(testBlockDatas, 257);
					}

					for (unsigned short i2 = 0; i2 < 16; i2++)
					{
						for (unsigned short j2 = 0; j2 < 16; j2++)
						{
							testBlockDatas[i2 + j2 * 16 + 1].setBlockRenderData(blockChunkLocationToShort(i2, rand() % 2, j2), 1);
							testBlockDatas[i2 + j2 * 16 + 1].setNearbyBlockAlpha(true, true, true, true, true, true);
							testBlockDatas[i2 + j2 * 16 + 1].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
						}
					}
					testBlockDatas[0].setBlockRenderData(blockChunkLocationToShort(0, 4, 0), 32);
					testBlockDatas[0].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
					testBlockDatas[0].setAlpha(true);

					chunk[i + 32 * k]->setBlockRenderDatas(testBlockDatas, 257);
				}
		fpController.getCamera()->getLocation()->moveTo(256, 10, 256);
	}
};

test_app Test;

int main()
{
	Test.run();
}