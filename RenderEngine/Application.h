#pragma once

#include "RenderEngine.h"
#include "ScreenManager.h"

//app instance
class	application;
extern	application* applicationInstance;

//applicaion
class application:public screen_manager
{
	friend class gl_manager;

private:
	//application base info
	const char*		_appName;
	const char*		_version;
	
	const size_vec	_windowSize;

protected:
	//init
	virtual void _init() = 0;

	//call when each tick
	virtual void _tickCall() = 0;

	//main loop
	void _mainLoop();

public:

	application(const char* appName, const char* version,const size_vec& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
	{
		applicationInstance = this;
	}

	//get instance
	static application& getInstance()
	{
		return *applicationInstance;
	}

	//run program
	void run();
};