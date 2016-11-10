
#include "FPC.h"
#include "FPCExtension.h"

fpc* bindedFPSController = nullptr;

//�󶨣����fpcΪnullptr��Ϊ������е�һ�˳ƿ�������
void bindFPC(fpc* fpc)
{
	//�Ƿ�Ϊ�գ�
	if (fpc == nullptr)
	{
		if (bindedFPSController == nullptr)
			return;

		application::getInstance().unregisterListener(bindedFPSController);

		//���
		bindedFPSController = fpc;

		//��ʾ���
		application::getInstance().showCursor();

		return;
	}
	
	//�Ƿ�ԭ���󶨹���������
	if (bindedFPSController != nullptr)
		application::getInstance().unregisterListener(bindedFPSController);
	else
		application::getInstance().hideCursor();

	bindedFPSController = fpc;

	application::getInstance().registerListener(bindedFPSController);
}

//�������
void fpc::cursorListener(double lastPosX, double lastPosY, double posX, double posY)
{
	//�ж�����������Ƿ��ǵ�ǰ����Ŀ�����
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

//����tick
void fpc::tickListener()
{
	//�ж�����������Ƿ��ǵ�ǰ����Ŀ�����
	if (bindedFPSController != this)
		return;

	//�����ٶ�
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
//��������
void fpc::keyListener(int key, int action)
{
	if (bindedFPSController != this)
		return;

	//�ٶ�״̬
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