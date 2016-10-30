#pragma once

#include "Camera.h"

class fps_controller
{
	friend void fpsKeyRefreshListener(int key, int action);

private:
	camera* _camera;

public:
	fps_controller(camera* camera) :_camera(camera) {}
};