#pragma once

#include "Camera.h"

class fps_controller
{
private:
	camera* _camera;

public:
	fps_controller(camera* camera) :_camera(camera) {}

	void refresh(int key, int action);
};