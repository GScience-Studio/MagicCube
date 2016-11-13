
#include "Application.h"
#include "GLManager.h"

#include <thread>

//tick call time
#define TICK_TIME 0.02

//program start time
double	startTime = 0.0;

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
	//save the efresh call time
	unsigned long long int	refreshCallTime = 0;

	//set start time
	startTime = glfwGetTime();
	
	//loop
	while (!_glInstance.windowShouldClose())
	{
		//time has refresh
		unsigned char refreshTime = 0;

		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//check time to call tick refresh
		while (glfwGetTime() - startTime - refreshCallTime * TICK_TIME >= TICK_TIME)
		{
			++refreshCallTime;
			++refreshTime;

			//tick call
			_tickRefresh(false, true);
		}
		if (refreshTime > 2)
			std::cout << "[Warning]Can't keep up!" << std::endl;

		//render
		_tickRefresh(true, false);

		_glInstance.swapBuffers();

		//pool event
		_glInstance.pollEvent();
	}
	//end
	_glInstance.terminate();
}