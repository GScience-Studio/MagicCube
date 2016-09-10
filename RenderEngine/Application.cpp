
#include "Application.h"
#include "GLManager.h"

application* applicationInstance;

void application::run()
{
	//call init
	_init();

	//init glManagerInstance
	gl_manager();

	//load window
	gl_manager::getInstance()._loadWindow();
}