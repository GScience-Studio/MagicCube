#pragma once

#include "GLManager.h"
#include "Canvas.h"

class render_manager
{
private:
	gl_manager& _glInstance = gl_manager::getInstance();

public:
	canvas addCanvas(screen& screen)
	{
		screen
		return canvas(buffer(_glInstance.genVAO(), _glInstance.genVBO()));
	}
};