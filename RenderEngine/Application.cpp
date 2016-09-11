
#include "Application.h"
#include "GLManager.h"

application* applicationInstance;

//run program
void application::run()
{
	//load window
	gl_manager::getInstance()._loadWindow();

	//init spritemanager
	initspriteManager();

	//call init
	_init();

	//main loop
	_mainLoop();
}
void application::_mainLoop()
{
	gl_manager glInstance = gl_manager::getInstance();

	while (!glInstance.windowShouldClose())
	{
		glInstance.clear(GL_COLOR_BUFFER_BIT);

		glInstance.poolEvent();

		glInstance.swapBuffers();
	}
	glInstance.terminate();
}