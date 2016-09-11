
#include "GLManager.h"

//instance
gl_manager gl_manager::_glInstance;

//create window
void gl_manager::_loadWindow()
{
	//get app instance
	application& appInstance = application::getInstance();

	//init glfw
	glfwInit();

	//load window
	_window = glfwCreateWindow(appInstance._windowSize.getHeight(), appInstance._windowSize.getWidth(), appInstance._appName, NULL, NULL);

	if (!_window)
	{
		glfwTerminate();
		
		message("Couldn't load the window", msgError,true);
	}

	//set context
	glfwMakeContextCurrent(_window);
}
