
#include "Application.h"
#include "GLManager.h"

//tick call time
#define TICK_TIME 0.01

//program start time
double	startTime = glfwGetTime();

//application instance
application* applicationInstance;

//run program
void application::run()
{
	//load window
	_glInstance._loadWindow();

	//load normal shader
	_glInstance.addShader("Normail3d.vert", "Normail3d.frag", _glInstance.appNormail3DShader);

	//call init
	init();

	//main loop
	_mainLoop();
}
void application::_mainLoop()
{
	unsigned long long int	refreshCallTime = 0;

	while (!_glInstance.windowShouldClose())
	{
		bool hasDraw = true;

		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//check time to call tick refresh
		while (glfwGetTime() - startTime - refreshCallTime * TICK_TIME >= TICK_TIME)
		{
			++refreshCallTime;

			//tick call
			_tickRefresh(hasDraw);

			hasDraw = false;
		}

		//pool event
		_glInstance.poolEvent();

		//swap buffer
		_glInstance.swapBuffers();
	}
	_glInstance.terminate();
}