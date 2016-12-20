
#include "../GSRenderEngine.h"
#include "../RenderEngine/ChunkRenderExtension.h"
#include "../RenderEngine/FPCExtension.h"

#define SIGHT 16

void buildMap(int chunkX, int chunkZ, unsigned int* chunkData);

scene_node* firstScene;
texture*	blockTexture;

class testChunk
{
public:
	unsigned int blockData[4096]{ 0 };

	chunk_render* chunkRender;

	void buildChunk(int chunkX,int chunkZ)
	{
		buildMap(chunkX, chunkZ, blockData);

		chunkRender = new chunk_render(firstScene, blockTexture);

		chunkRender->setChunkLocation(chunkX, 0, chunkZ);
	}

	void refreshChunkRenderData()
	{
		block_render_data blockRenderData[4096];

		for (unsigned short i = 0; i < 4096; i++)
		{
			blockRenderData[i].setBlockRenderData(i, blockData[i]);
			blockRenderData[i].setNearbyBlockAlpha(true, true, true, true, true, true);
			blockRenderData[i].setNearbyBlockLight(15, 15, 15, 15, 15, 15);
			blockRenderData[i].setAlpha(false);
		}
		chunkRender->setBlockRenderDatas(blockRenderData, 4096);
	}
	~testChunk()
	{
		delete(chunkRender);
	}
};

class test_app :public application
{
private:
	unsigned int _tick;

public:
	fpc fpController = fpc(getGlobalCamera());

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
		
		testChunk* chunks = new testChunk[SIGHT * 2 * SIGHT * 2];

		double startTime = glfwGetTime();

		for (int i = 0; i < SIGHT * 2; i++)
			for (int j = 0; j < SIGHT * 2; j++)
			{
				chunks[i * SIGHT * 2 + j].buildChunk(i, j);
				chunks[i * SIGHT * 2 + j].refreshChunkRenderData();
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