
#include "../WorldManager.h"
#include <iostream>
#include "../WorldManager/Location.h"

int main()
{
	world_manager* testWorldManager = new world_manager();

	std::cout << "Loading world...." << std::endl;

	testWorldManager->tickListener();

	std::cout << "Finish!" << std::endl;

	while (true)
	{
		uint32_t x;
		uint32_t y;
		uint32_t z;

		std::cout << "Please enter the location you want to transport:" << std::endl;

		std::cout << "X:" << std::endl;
		std::cin >> x;

		std::cout << "Y:" << std::endl;
		std::cin >> y;

		std::cout << "Z:" << std::endl;
		std::cin >> z;

		std::cout << "Succese to transport!" << std::endl;

		testWorldManager->transport(location(&testWorldManager->testWorld, x, y, z));
		testWorldManager->tickListener();
	}
	delete(testWorldManager);

	while (true);
}