#pragma once

#define TICK_TIME 0.02

#include "RenderEngine.h"
#include "SceneNodeManager.h"
#include "InputCallbackManager.h"
#include "ExtensionManager.h"

#include <condition_variable>

//app instance
class	application;
extern	application* applicationInstance;

/*
applicaion
The base class of a program.
It's a listener and it also is a listener manager.
So in there you can add your own listener function and register or unregister listener.
And it's also a scene manager witch can add and remove scene.
You can add more thing by extension such as shader and new kind of render node(some of them it's not necessary to add by extension manager)
*/
class application :public scene_node_manager, public input_callback_manager, protected extension_manager, public input_callback
{
	friend class listener_manager;

protected:
	//application base info
	const char*		_appName;
	const char*		_version;

	const size_vec	_windowSize;

private:
	//thread and lock
	std::thread _eventThread;
	std::mutex  _eventThreadLock;

	std::condition_variable _tickEnableFlag;

	//tick call time
	std::atomic_uint16_t _tickCallTime = 0;

	//whether the program is end
	volatile std::atomic_bool _isClose = false;

	//has init the game
	volatile std::atomic_bool _initialization = false;

	//gl instance
	gl_manager& _glInstance = gl_manager::getInstance();

	//main loop
	void _mainLoop();

	//refresh(a tick is 0.01s)
	void _tickRefresh(bool draw, bool refresh);

	//program run time and tick
	double			_appStartTime = glfwGetTime();
	unsigned long	_totalTickCount = 0;

	/*
	* event thread main
	* made by GM2000
	*/
	void _eventThreadMain();

public:
	//cursor info
	std::atomic_bool isCursorEnable = true;

	application(const char* appName, const char* version, const size_vec& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
	{
		applicationInstance = this;
	}

	virtual void initResources() = 0;

	//gen texture
	texture* genTexture(std::initializer_list<const char*> fileName, GLuint count)
	{
		return _glInstance.genTexture((const char**)fileName.begin(), count);
	}
	texture* genTexture(const char* fileName[], GLuint count)
	{
		return _glInstance.genTexture(fileName, count);
	}
	//init
	virtual void init() = 0;

	//get instance
	static application& getInstance()
	{
		return *applicationInstance;
	}
	
	//run program
	void run();

	//set cursor input mode
	void hideCursor()
	{
		isCursorEnable.store(false);
	}
	void showCursor()
	{
		isCursorEnable.store(true);
	}
};