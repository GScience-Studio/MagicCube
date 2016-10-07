
#include "Application.h"
#include "GLManager.h"
#include "NormalShader.h"

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

	//load normal 3d shader
	_glInstance.genShader("Normal3d.vert", "Normal3d.frag", normal3DShader);

	//load normal 2d shader
	_glInstance.genShader("Normal3d.vert", "Normal3d.frag", normal2DShader);

	//call init
	init();

	//main loop
	_mainLoop();
}
//game main loop
void application::_mainLoop()
{
	//save the efresh call time
	unsigned long long int	refreshCallTime = 0;

	//loop
	while (!_glInstance.windowShouldClose())
	{
		//has draw
		bool hasDraw = true;

		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//check time to call tick refresh
		while (glfwGetTime() - startTime - refreshCallTime * TICK_TIME >= TICK_TIME)
		{
			++refreshCallTime;

			//tick call
			_tickRefresh(hasDraw);

			if (hasDraw)
			{
				hasDraw = false;

				//swap buffer
				_glInstance.swapBuffers();
			}
		}

		//pool event
		_glInstance.poolEvent();
	}
	//end
	_glInstance.terminate();
}