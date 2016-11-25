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
	std::atomic_bool _isClose = false;

	//has init the game
	std::atomic_bool _initialization = false;

	//cursor input mode
	bool _isCursorEnable = true;

	//gl instance
	gl_manager& _glInstance = gl_manager::getInstance();

	//main loop
	void _mainLoop();

	//refresh(a tick is 0.01s)
	void _tickRefresh();

	//program run time and tick
	double			_appStartTime = glfwGetTime();
	unsigned long	_totalTickCount = 0;

	/*
	* event thread main
	* made by GM2000
	*/
	void _eventThreadMain();

public:
	std::atomic_bool isCursorEnableSynch = true;

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
	
	/*
	* enter point of an GS Engine program.
	* the program will run after you call this function
	* thread-safety: can called in any thread but only can call once
	* made by GM2000
	*/
	void run();

	/*
	* hide the cursor.
	* thread-safety: can be called in any thread.
	* made by GM2000
	*/
	void hideCursor()
	{
		isCursorEnableSynch.store(false);
	}

	/*
	* show the cursor.
	* thread-safety: can be called in any thread.
	* made by GM2000
	*/
	void showCursor()
	{
		isCursorEnableSynch.store(true);
	}
};