
#include "../WorldManager.h"
#include <iostream>
#include "../WorldManager/Location.h"

int main()
{
	world_manager* testWorldManager = new world_manager();

	world* world = testWorldManager->loadWorld("World 1");

	testWorldManager->transport(location(world, 0, 0, 0));

	std::cout << "Loading world...." << std::endl;

	testWorldManager->tickListener();

	std::cout << "Finish!" << std::endl;

	while (true)
	{
		uint32_t x;
		uint32_t y;
		uint32_t z;

		std::cout << "random tick (1000 times)" << std::endl;

		for (unsigned int i = 0; i < 1000; i++)
		{
			testWorldManager->tickListener();
		}
		std::cout << "Please enter the location you want to transport:" << std::endl;

		std::cout << "X:" << std::endl;
		std::cin >> x;

		std::cout << "Y:" << std::endl;
		std::cin >> y;

		std::cout << "Z:" << std::endl;
		std::cin >> z;

		std::cout << "Succese to transport!" << std::endl;

		testWorldManager->transport(location(world, x, y, z));
	}
	delete(testWorldManager);

	while (true);
}