
#include "FPSController.h"
#include "FPSControllerExtension.h"

fps_controller* bindedFPSController;

void bindFPSController(fps_controller* fpsController)
{
	bindedFPSController = fpsController;
}

void fpsKeyRefreshListener(int key, int action)
{
	bindedFPSController->_camera->getLocation()->move(
		key == GLFW_KEY_A || key == GLFW_KEY_D ? key == GLFW_KEY_A ? 0.1 : -0.1 : 0.0,
		key == GLFW_KEY_SPACE || key == GLFW_KEY_LEFT_SHIFT ? key == GLFW_KEY_SPACE ? 0.1 : -0.1 : 0.0,
		key == GLFW_KEY_W || key == GLFW_KEY_S ? key == GLFW_KEY_W ? 0.1 : -0.1 : 0.0);

	bindedFPSController->_camera->getAngle()->rotate(
		0.0f, key == GLFW_KEY_Q || key == GLFW_KEY_E ? key == GLFW_KEY_Q ? 0.1f : -0.1f : 0.0f);

	std::cout << bindedFPSController->_camera->getLocation()->getX() << "," << bindedFPSController->_camera->getLocation()->getY() << "," << bindedFPSController->_camera->getLocation()->getZ() << "," << std::endl;
}

void fps_controller_extension::init()
{
	//register listener
	application::getInstance().registerListener(fpsKeyRefreshListener);
}