
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
		_glInstance.clear(GL_COLOR_BUFFER_BIT);

		//tick call
		_tickRefresh();

		_glInstance.poolEvent();

		_glInstance.swapBuffers();
	}
	_glInstance.terminate();
}