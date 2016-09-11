
#include "Application.h"
#include "GLManager.h"

application* applicationInstance;

//run program
void application::run()
{
	//call init
	_init();

	//init glManagerInstance
	gl_manager();

	//load window
	gl_manager::getInstance()._loadWindow();

	//main loop
	_mainLoop();
}
void application::_mainLoop()
{
	gl_manager glInstance = gl_manager::getInstance();

	while (!gl_manager::getInstance().windowShouldClose())
	{
		glInstance.clear(GL_COLOR_BUFFER_BIT);

		glInstance.poolEvent();

		glInstance.swapBuffers();
	}
	glInstance.terminate();
}