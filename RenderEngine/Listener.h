#pragma once

#include "RenderEngine.h"

class listener
{
	friend class listener_manager;

public:
	//keyboard function
	virtual void keyListener(int key, int action) {}

	//tick function
	virtual void tickListener() {}

	//cursor listener function
	virtual void cursorListener(double lastPosX, double lastPosY, double posX, double posY) {}

	//window size change listener function
	virtual void windowsSizeChangeListener(int width, int height) {}

	//char input listener function
	virtual void charInputCallback(const char* chars) {}

	//destructor
	virtual ~listener() {}
};