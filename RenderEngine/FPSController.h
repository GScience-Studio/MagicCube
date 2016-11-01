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
	//绑定的相机
	camera* _camera;

	//各个方向的速度
	vec<float, 3> _speed{ 0.0f,0.0f,0.0f };
	//各个方向的速度状态
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

public:
	fps_controller(camera* camera) :_camera(camera) {}

	//tick刷新
	void tickListener();
	//键盘操作
	void keyListener(int key, int action);
};