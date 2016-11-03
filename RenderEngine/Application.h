#pragma once

#include "RenderEngine.h"
#include "SceneManager.h"
#include "ListenerManager.h"
#include "ExtensionManager.h"

//app instance
class	application;
extern	application* applicationInstance;

//applicaion
class application :public scene_manager, public listener_manager, public extension_manager
{
	friend class listener_manager;

protected:
	//application base info
	const char*		_appName;
	const char*		_version;

	const size_vec	_windowSize;

private:
	//gl instance
	gl_manager& _glInstance = gl_manager::getInstance();

	//main loop
	void _mainLoop();

	//refresh(a tick is 0.01s)
	void _tickRefresh(bool draw, bool refresh);
public:
	application(const char* appName, const char* version, const size_vec& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
	{
		applicationInstance = this;
	}

	texture genTexture(char* fileName[], GLuint count)
	{
		return _glInstance.genTexture(fileName, count);
	}
	//init
	virtual void init() = 0;

	//call when each tick
	virtual void tickCall() {};

	//get instance
	static application& getInstance()
	{
		return *applicationInstance;
	}

	//run program
	void run();
};