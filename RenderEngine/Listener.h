#pragma once

#include "RenderEngine.h"

/*
* listener is a way to get user input or something 
* will call in program.

* thread-safety: all listener will only call in event thread

made by GM2000
*/
class listener
{
	friend class listener_manager;

private:
	//save the thread ID to automatic call events
	std::thread::id _threadID;

public:
	//keyboard function
	virtual void keyListener(int key, int action) {}

	//tick function
	virtual void tickListener() {}

	//cursor listener function
	virtual void cursorListener(double lastPosX, double lastPosY, double posX, double posY) {}

	//window size change listener function
	virtual void windowsSizeChangeListener(int width, int height) {}

	//destructor
	virtual ~listener() {}
};