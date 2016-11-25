
#include "Application.h"
#include "GLManager.h"

#include <thread>

//application instance
application* applicationInstance;

//tick listener
void tickListenerRefresh();

//exception
void initExceptionCallback();

void application::run()
{
	//init exception
	initExceptionCallback();

	//load window
	_glInstance._loadWindow(_windowSize,_appName);

	//init listener
	_initInputCallbackManager(_glInstance._window);

	//register listeners
	registerInputCallback(&_glInstance);
	registerInputCallback(this);

	//init resources
	initResources();

	//start event thread and wait for init
	_eventThread = std::thread(&application::_eventThreadMain, this);
	_eventThread.detach();

	while (!_initialization.load());

	//main loop
	_mainLoop();

	//wait for thread end
	_isClose.store(true);

	_tickEnableFlag.notify_one();

	while (_isClose.load());
}
//tick call
void application::_tickRefresh()
{
	tickListenerRefresh();
}
//game main loop
void application::_mainLoop()
{
	//loop
	while (!_glInstance.windowShouldClose())
	{
		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
		double getTime = glfwGetTime();

		//get pass tick
		uint16_t passTickCount = (uint16_t)((getTime - _appStartTime - _totalTickCount * TICK_TIME) / TICK_TIME);

		//has tick?
		if (passTickCount != 0)
		{
			_totalTickCount += passTickCount;
			_tickCallTime.store(_tickCallTime.load() + passTickCount);

			//wake up tick thread
			_tickEnableFlag.notify_all();
		}
		//refresh queue
		_glInstance._refreshQueue();

		//scene refresh
		_sceneRefresh();

		//render
		_sceneDraw();

		_glInstance.swapBuffers();

		//pool event
		_glInstance.pollEvent();

		//get cursor input mode
		bool getCursorNewInputMode = isCursorEnableSynch.load();

		if (_isCursorEnable != getCursorNewInputMode)
		{
			//set new mouse input mode
			_isCursorEnable = getCursorNewInputMode;

			//set mouse
			if (_isCursorEnable)
				glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			else
				glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
	//end
	_glInstance.terminate();
}

void application::_eventThreadMain()
{
	//init application and thread
	init();

	_initialization.store(true);

	while (!_isClose.load())
	{
		_tickEnableFlag.wait((std::unique_lock<std::mutex>)_eventThreadLock);

		//tick call
		while (_tickCallTime.load() != 0)
		{
			_tickCallTime.store(_tickCallTime.load() - 1);

			_tickRefresh();
		}

		//refresh event
		refreshEvent();
	}
	_isClose.store(false);
}