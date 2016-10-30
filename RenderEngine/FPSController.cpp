
#include "FPSController.h"
#include "FPSControllerExtension.h"

fps_controller* bindedFPSController;

void bindFPSController(fps_controller* fpsController)
{
	bindedFPSController = fpsController;
}

//监听tick
void fpsTickCall()
{
	//设置速度
	for (unsigned char i=0;i<3;i++)
		if (bindedFPSController->speedState[i] != fps_controller::fps_controller::SPEED_STOP && bindedFPSController->speed[i] < 0.1f && bindedFPSController->speed[i] > -0.1f)
			bindedFPSController->speed.set(i, bindedFPSController->speed[i] + (bindedFPSController->speedState[i] == fps_controller::fps_controller::SPEED_UP ? 0.005f : -0.005f));
		else if (bindedFPSController->speedState[i] == fps_controller::fps_controller::SPEED_STOP && bindedFPSController->speed[i] != 0.0f)
			bindedFPSController->speed.set(i, bindedFPSController->speed[i] + (bindedFPSController->speed[i] < 0.0f ? 0.005f : -0.005f));

	bindedFPSController->_camera->getLocation()->move(
		bindedFPSController->speed[1],
		0.0,
		bindedFPSController->speed[0]);
}
//监听键盘
void fpsKeyRefreshListener(int key, int action)
{
	//速度状态
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			bindedFPSController->speedState.set(0, fps_controller::fps_controller::SPEED_UP);
		else if (key == GLFW_KEY_S)
			bindedFPSController->speedState.set(0, fps_controller::fps_controller::SPEED_DOWN);
		else if (key == GLFW_KEY_A)
			bindedFPSController->speedState.set(1, fps_controller::fps_controller::SPEED_UP);
		else if (key == GLFW_KEY_D)
			bindedFPSController->speedState.set(1, fps_controller::fps_controller::SPEED_DOWN);
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)
			bindedFPSController->speedState.set(0, fps_controller::fps_controller::SPEED_STOP);
		else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
			bindedFPSController->speedState.set(1, fps_controller::fps_controller::SPEED_STOP);
	}

	std::cout << bindedFPSController->_camera->getLocation()->getX() << "," << bindedFPSController->_camera->getLocation()->getY() << "," << bindedFPSController->_camera->getLocation()->getZ() << "," << std::endl;
}

void fps_controller_extension::init()
{
	//register listener
	application::getInstance().registerListener(fpsKeyRefreshListener);
	application::getInstance().registerListener(fpsTickCall);
}