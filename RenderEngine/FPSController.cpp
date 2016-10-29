
#include "FPSController.h"

void fps_controller::refresh(int key, int action)
{
	_camera->getLocation()->move(
		key == GLFW_KEY_A || key == GLFW_KEY_D ? key == GLFW_KEY_A ? 0.1 : -0.1 : 0.0,
		key == GLFW_KEY_SPACE || key == GLFW_KEY_LEFT_SHIFT ? key == GLFW_KEY_SPACE ? 0.1 : -0.1 : 0.0,
		key == GLFW_KEY_W || key == GLFW_KEY_S ? key == GLFW_KEY_W ? 0.1 : -0.1 : 0.0);

	std::cout << _camera->getLocation()->getX() << "," << _camera->getLocation()->getY() << "," << _camera->getLocation()->getZ() << "," << std::endl;
}