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
	camera* _camera;

	//�Ƿ�Ϊ����ģʽ
	bool _isFastMode = false;

	//����������ٶ�
	vec<double, 3> _speed{ 0.0f,0.0f,0.0f };

	//����������ٶ�״̬
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

	//�������Ϣ
	location<double>&	_location	= *_camera->getLocation();
	angle&				_angle		= *_camera->getAngle();

public:
	fpc(camera* camera) :_camera(camera) {}
	
	//��ȡλ��
	camera* getCamera()
	{
		return _camera;
	}

	//tickˢ��
	void tickListener();

	//���̲���
	void keyListener(int key, int action);

	//����ƶ�
	void cursorListener(double lastPosX, double lastPosY, double posX, double posY);
};