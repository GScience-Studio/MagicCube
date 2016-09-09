
#include "RenderManager.h"

render_manager* renderManagerInstance;

void render_manager::_loadWindow()
{
	//init glfw
	glfwInit();

	//load window
	_window = glfwCreateWindow(600, 600, application::getInstance()._appName, NULL, NULL);
}