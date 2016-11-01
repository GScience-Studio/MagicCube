#pragma once

#include "ListenerManager.h"
#include "Camera.h"

class fps_controller :public listener
{
	enum speed_state
	{
		SPEED_UP, SPEED_STOP, SPEED_DOWN
	};
private:
	//�󶨵����
	camera* _camera;

	//����������ٶ�
	vec<float, 3> _speed{ 0.0f,0.0f,0.0f };
	//����������ٶ�״̬
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

public:
	fps_controller(camera* camera) :_camera(camera) {}

	//tickˢ��
	void tickListener();
	//���̲���
	void keyListener(int key, int action);
};