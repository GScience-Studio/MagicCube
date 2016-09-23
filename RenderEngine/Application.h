#pragma once

#include "RenderEngine.h"
#include "SceneManager.h"

//app instance
class	application;
extern	application* applicationInstance;

//applicaion
class application :public scene_manager
{
	friend class gl_manager;

protected:
	//application base info
	const char*		_appName;
	const char*		_version;

	const size_vec	_windowSize;

private:
	//gl instance
	gl_manager _glInstance = gl_manager::getInstance();

	//main loop
	void _mainLoop();

	//refresh(a tick is 0.01s)
	void _tickRefresh()
	{
		//user call
		tickCall();

		//scene refresh
		_sceneRefreshAndDraw();
	}
public:
	application(const char* appName, const char* version, const size_vec& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
	{
		applicationInstance = this;
	}

	//init
	virtual void init() = 0;

	//call when each tick
	virtual void tickCall() = 0;

	//get instance
	static application& getInstance()
	{
		return *applicationInstance;
	}

	//run program
	void run();
};