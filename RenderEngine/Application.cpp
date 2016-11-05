
#include "Application.h"
#include "GLManager.h"

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

	//call init
	init();

	//init listener
	_initListenerManager(_glInstance._window);

	//main loop
	_mainLoop();
}
//tick call
void application::_tickRefresh(bool draw, bool refresh)
{
	if (refresh)
	{
		//user call
		tickCall();

		//listener call
		tickListenerRefresh();
	}
	if (draw)
	{
		//scene refresh
		_sceneRefreshAndDraw(draw);
	}
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
		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		unsigned char refreshTime = 0;

		//check time to call tick refresh
		while (glfwGetTime() - startTime - refreshCallTime * TICK_TIME >= TICK_TIME)
		{
			++refreshCallTime;
			++refreshTime;

			if (refreshTime > 2)
				std::cout << "[Warning]Can't keep up!" << std::endl;

			if (refreshTime > 20)
			{
				std::cout << "[Warning]Drop!" << std::endl;

				continue;
			}

			//tick call
			_tickRefresh(false, true);
		}
		_tickRefresh(true, false);
		_glInstance.swapBuffers();

		//pool event
		_glInstance.poolEvent();
	}
	//end
	_glInstance.terminate();
}