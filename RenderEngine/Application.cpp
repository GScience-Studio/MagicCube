
#include <windows.h>

#include "Application.h"
#include "GLManager.h"

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
	while (!_glInstance.windowShouldClose())
	{
		double startTime = glfwGetTime();

		//clear screen
		_glInstance.clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//tick call
		_tickRefresh();

		//pool event
		_glInstance.poolEvent();

		//swap buffer
		_glInstance.swapBuffers();

		//wait
		while (glfwGetTime() - startTime <= 0.0166666666666667)
		{
			double nowTime = glfwGetTime();

			if (nowTime - startTime <= 0.001010101010101)
				Sleep((int)((0.0166666666666667 - nowTime + startTime) * 990));
		}
		
	}
	_glInstance.terminate();
}