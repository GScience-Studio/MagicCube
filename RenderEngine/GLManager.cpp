
#include "GLManager.h"

gl_manager* glManagerInstance;

void gl_manager::_loadWindow()
{
	//get app instance
	application& appInstance = application::getInstance();

	//init glfw
	glfwInit();

	//load window
	_window = glfwCreateWindow(appInstance._windowSize.getHeight(), appInstance._windowSize.getWidth(), appInstance._appName, NULL, NULL);
}