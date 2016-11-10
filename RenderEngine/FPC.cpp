
#include "FPC.h"
#include "FPCExtension.h"

fpc* bindedFPSController = nullptr;

//绑定（如果fpc为nullptr则为解绑所有第一人称控制器）
void bindFPC(fpc* fpc)
{
	//是否为空？
	if (fpc == nullptr)
	{
		if (bindedFPSController == nullptr)
			return;

		application::getInstance().unregisterListener(bindedFPSController);

		//解绑
		bindedFPSController = fpc;

		//显示光标
		application::getInstance().showCursor();

		return;
	}
	
	//是否原来绑定过控制器？
	if (bindedFPSController != nullptr)
		application::getInstance().unregisterListener(bindedFPSController);
	else
		application::getInstance().hideCursor();

	bindedFPSController = fpc;

	application::getInstance().registerListener(bindedFPSController);
}

//监听鼠标
void fpc::cursorListener(double lastPosX, double lastPosY, double posX, double posY)
{
	//判断这个控制器是否是当前激活的控制器
	if (bindedFPSController != this)
		return;

	_camera->getAngle()->rotate((lastPosY - posY) * 0.001f, (lastPosX - posX) * 0.001f);

	if (_angle.getPosX() > PI / 2.0f)
		_camera->getAngle()->setPosX(PI / 2.0f);
	else if (_angle.getPosX() < -PI / 2.0f)
		_camera->getAngle()->setPosX(-PI / 2.0f);

	if (_angle.getPosY() > PI * 2.0f || _angle.getPosY() < -PI * 2.0f)
		_camera->getAngle()->setPosY(0.0f);
}

//监听tick
void fpc::tickListener()
{
	//判断这个控制器是否是当前激活的控制器
	if (bindedFPSController != this)
		return;

	//设置速度
	for (unsigned char i = 0; i < 3; i++)
		if (_speedState[i] != SPEED_STOP && _speed[i] < 0.1f && _speed[i] > -0.1f)
			_speed[i] += _speedState[i] == SPEED_UP ? 0.005f : -0.005f;
		else if (_speedState[i] == SPEED_STOP && _speed[i] != 0.0f)
			if (_speed[i] <= 0.005 && _speed[i] >= -0.005)
				_speed[i] = 0.0f;
			else
				_speed[i] += _speed[i] < 0.0f ? 0.005f : -0.005f;
	
	if (_isFastMode == true)
		_camera->getLocation()->move(
			(_speed[X] + 5) * cos(_angle.getPosY()) + (_speed[Z] + 5) * sin(_angle.getPosY()),
			0.0,
			(_speed[Z] +  5) * cos(_angle.getPosY()) - (_speed[X] + 5) * sin(_angle.getPosY()));
	else
		_camera->getLocation()->move(
			_speed[X] * cos(_angle.getPosY()) + _speed[Z] * sin(_angle.getPosY()),
			0.0,
			_speed[Z] * cos(_angle.getPosY()) - _speed[X] * sin(_angle.getPosY()));
}
//监听键盘
void fpc::keyListener(int key, int action)
{
	if (bindedFPSController != this)
		return;

	//速度状态
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			bindedFPSController->_speedState.set(Z, SPEED_UP);
		else if (key == GLFW_KEY_S)
			bindedFPSController->_speedState.set(Z, SPEED_DOWN);
		else if (key == GLFW_KEY_A)
			bindedFPSController->_speedState.set(X, SPEED_UP);
		else if (key == GLFW_KEY_D)
			bindedFPSController->_speedState.set(X, SPEED_DOWN);
		else if (key == GLFW_KEY_LEFT_SHIFT)
			_isFastMode = true;
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W || key == GLFW_KEY_S)
			bindedFPSController->_speedState.set(Z, SPEED_STOP);
		else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
			bindedFPSController->_speedState.set(X, SPEED_STOP);
		else if (key == GLFW_KEY_LEFT_SHIFT)
			_isFastMode = false;
	}
}