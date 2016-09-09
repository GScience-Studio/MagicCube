#pragma once

#include "RenderEngine.h"

//app instance
class	application;
extern	application* applicationInstance;

//applicaion
class application
{
	friend class render_manager;

	//application base info
	const char* _appName;
	const char* _version;
	
	const size	_windowSize;

	//init
	virtual void init() = 0;

	//call when each tick
	virtual void tickCall() = 0;

public:

	application(const char* appName, const char* version,const size& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
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