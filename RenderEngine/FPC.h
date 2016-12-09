#pragma once

#include "InputCallback.h"
#include "Camera.h"

//第一人称控制器
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
	//绑定的相机
	camera* _camera;

	//是否为快速模式
	bool _isFastMode = false;

	//各个方向的速度
	vec<double, 3> _speed{ 0.0f,0.0f,0.0f };

	//各个方向的速度状态
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

	//简化相机信息
	location<double>&	_location	= *_camera->getLocation();
	angle&				_angle		= *_camera->getAngle();

public:
	fpc(camera* camera) :_camera(camera) {}
	
	//获取位置
	camera* getCamera()
	{
		return _camera;
	}

	//tick刷新
	void tickListener();

	//键盘操作
	void keyListener(int key, int action);

	//鼠标移动
	void cursorListener(double lastPosX, double lastPosY, double posX, double posY);
};