#pragma once

#include "InputCallback.h"
#include "Camera.h"

//��һ�˳ƿ�����
class fpc :public input_callback
{
	friend void bindFPC(fpc*);

	enum speed_state
	{
		SPEED_UP, SPEED_STOP, SPEED_DOWN
	};
	enum speed_directon
	{
		X, Y, Z
	};
private:
	//�󶨵����
	camera_synchronize*	_renderCamera;
	camera			_fpcCamera;

	//�Ƿ�Ϊ����ģʽ
	bool _isFastMode = false;

	//����������ٶ�
	vec<double, 3> _speed{ 0.0f,0.0f,0.0f };

	//����������ٶ�״̬
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

	//�������Ϣ
	location<double>&	_location	= *_fpcCamera.getLocation();
	angle&				_angle		= *_fpcCamera.getAngle();

	//������Ⱦ���
	void _setRenderCamera()
	{
		_renderCamera->getLocation()->setX(_fpcCamera.getLocation()->getX());
		_renderCamera->getLocation()->setY(_fpcCamera.getLocation()->getY());
		_renderCamera->getLocation()->setZ(_fpcCamera.getLocation()->getZ());

		_renderCamera->getAngle()->setPosX(_fpcCamera.getAngle()->getPosX());
		_renderCamera->getAngle()->setPosY(_fpcCamera.getAngle()->getPosY());
	}

public:
	fpc(camera_synchronize* renderCamera) :_renderCamera(renderCamera)
	{
		_fpcCamera.getLocation()->setX(_renderCamera->getLocation()->getX());
		_fpcCamera.getLocation()->setY(_renderCamera->getLocation()->getY());
		_fpcCamera.getLocation()->setZ(_renderCamera->getLocation()->getZ());

		_fpcCamera.getAngle()->setPosX(_renderCamera->getAngle()->getPosX());
		_fpcCamera.getAngle()->setPosY(_renderCamera->getAngle()->getPosY());
	}
	
	//��ȡλ��
	camera* getCamera()
	{
		return &_fpcCamera;
	}

	//tickˢ��
	void tickListener();

	//���̲���
	void keyListener(int key, int action);

	//����ƶ�
	void cursorListener(double lastPosX, double lastPosY, double posX, double posY);
};