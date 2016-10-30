#pragma once

#include "Camera.h"

class fps_controller
{
	friend void fpsKeyRefreshListener(int key, int action);
	friend void fpsTickCall();

	enum speed_state
	{
		SPEED_UP, SPEED_STOP, SPEED_DOWN
	};
private:
	//�󶨵����
	camera* _camera;

	//����������ٶ�
	vec<float, 3> speed{ 0.0f,0.0f,0.0f };
	//����������ٶ�״̬
	vec<speed_state, 3> speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };
public:
	fps_controller(camera* camera) :_camera(camera) {}
};