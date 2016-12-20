
#include "../WorldManager.h"
#include <iostream>

int main()
{
	world_manager* testWorldManager = new world_manager();

	int time = 0;

	for (unsigned int i = 0; i < 1000000; i++)
		testWorldManager->testWorld.addChunk(i, 0, 0);

	delete(testWorldManager);

	while (true);
}