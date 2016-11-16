
#include "Application.h"
#include "GLManager.h"

#include <thread>

//application instance
application* applicationInstance;

//tick listener
void tickListenerRefresh();

//run program
void application::run()
{
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

	while (!_initialization);

	//main loop
	_mainLoop();

	//wait for thread end
	_isClose = true;

	while (_isClose);
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

		//refresh queue
		_glInstance._refreshQueue();

		//render
		_tickRefresh(true, false);

		_glInstance.swapBuffers();

		//pool event
		_glInstance.pollEvent();

		//set mouse
		if (isCursorEnable)
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

	_initialization = true;

	while (!_isClose)
	{
		//get the time to next event call
		double callNextEventCallTime = glfwGetTime() - _totalTickCount * TICK_TIME - _appRunTime - TICK_TIME;
		
		//automatic sleep
		if (callNextEventCallTime > 0.0f)
			std::this_thread::sleep_for(std::chrono::milliseconds((unsigned int)(callNextEventCallTime * 1000)));
		
		while (glfwGetTime() - _totalTickCount * TICK_TIME - _appRunTime >= TICK_TIME)
		{
			_totalTickCount++;

			_tickRefresh(false, true);
		}
	}
	_isClose = false;
}