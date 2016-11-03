
#include "FPSController.h"
#include "FPSControllerExtension.h"

fps_controller* bindedFPSController = nullptr;

//绑定
void bindFPSController(fps_controller* fpsController)
{
	if (bindedFPSController != nullptr)
		application::getInstance().unregisterListener(bindedFPSController);

	bindedFPSController = fpsController;

	application::getInstance().registerListener(bindedFPSController);
}

//监听tick
void fps_controller::tickListener()
{
	//设置速度
	for (unsigned char i = 0; i < 3; i++)
		if (bindedFPSController->_speedState[i] != fps_controller::fps_controller::SPEED_STOP && bindedFPSController->_speed[i] < 0.1f && bindedFPSController->_speed[i] > -0.1f)
			bindedFPSController->_speed.set(i, bindedFPSController->_speed[i] + (bindedFPSController->_speedState[i] == fps_controller::fps_controller::SPEED_UP ? 0.005f : -0.005f));
		else if (bindedFPSController->_speedState[i] == fps_controller::fps_controller::SPEED_STOP && bindedFPSController->_speed[i] != 0.0f)
			if (bindedFPSController->_speed[i] <= 0.005 && bindedFPSController->_speed[i] >= -0.005)
				bindedFPSController->_speed.set(i, 0.0f);
			else
				bindedFPSController->_speed.set(i, bindedFPSController->_speed[i] + (bindedFPSController->_speed[i] < 0.0f ? 0.005f : -0.005f));

	bindedFPSController->_camera->getLocation()->move(
		bindedFPSController->_speed[1],
		0.0,
		bindedFPSController->_speed[0]);
}
//监听键盘
void fps_controller::keyListener(int key, int action)
{
	//速度状态
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			bindedFPSController->_speedState.set(0, fps_controller::fps_controller::SPEED_UP);
		else if (key == GLFW_KEY_S)
			bindedFPSController->_speedState.set(0, fps_controller::fps_controller::SPEED_DOWN);
		else if (key == GLFW_KEY_A)
			bindedFPSController->_speedState.set(1, fps_controller::fps_controller::SPEED_UP);
		else if (key == GLFW_KEY_D)
			bindedFPSController->_speedState.set(1, fps_controller::fps_controller::SPEED_DOWN);
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)
			bindedFPSController->_speedState.set(0, fps_controller::fps_controller::SPEED_STOP);
		else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
			bindedFPSController->_speedState.set(1, fps_controller::fps_controller::SPEED_STOP);
	}
}