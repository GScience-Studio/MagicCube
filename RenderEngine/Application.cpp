
#include "Application.h"
#include "GLManager.h"

#include <thread>

//application instance
application* applicationInstance;

//tick listener
void tickListenerRefresh();

//exception
void initExceptionCallback();

//run program
void application::run()
{
	//init exception
	initExceptionCallback();

	//load window
	_glInstance._loadWindow(_windowSize,_appName);

	//init listener
	_initListenerManager(_glInstance._window);

	//register listeners
	registerListener(&_glInstance);
	registerListener(this);

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
void application::_tickRefresh(bool draw, bool refresh)
{
	if (refresh)
	{
		//listener call
		tickListenerRefresh();
	}
	//scene refresh
	_sceneRefreshAndDraw(draw);
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

		//render
		_tickRefresh(true, false);

		_glInstance.swapBuffers();

		//pool event
		_glInstance.pollEvent();

		//set mouse
		if (isCursorEnable.load())
			glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		else
			glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

		while (_tickCallTime.load() != 0)
		{
			_tickCallTime.store(_tickCallTime.load() - 1);

			_tickRefresh(false, true);
		}
	}
	_isClose.store(false);
}