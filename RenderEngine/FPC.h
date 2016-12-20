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
	camera_synchronize*	_renderCamera;
	camera			_fpcCamera;

	//是否为快速模式
	bool _isFastMode = false;

	//各个方向的速度
	vec<double, 3> _speed{ 0.0f,0.0f,0.0f };

	//各个方向的速度状态
	vec<speed_state, 3> _speedState{ SPEED_STOP ,SPEED_STOP ,SPEED_STOP };

	//简化相机信息
	location<double>&	_location	= *_fpcCamera.getLocation();
	angle&				_angle		= *_fpcCamera.getAngle();

	//设置渲染相机
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
	
	//获取位置
	camera* getCamera()
	{
		return &_fpcCamera;
	}

	//tick刷新
	void tickListener();

	//键盘操作
	void keyListener(int key, int action);

	//鼠标移动
	void cursorListener(double lastPosX, double lastPosY, double posX, double posY);
};