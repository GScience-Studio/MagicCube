#pragma once

#include "RenderEngine.h"
#include "Application.h"

//save the instance
class	gl_manager;
extern	gl_manager* glManagerInstance;

/*
rendermanager
it is used to do the basic thing
with opengl such as create an window
or create vao,vbo
*/
class gl_manager
{
	//sone function only can be use when the app start run
	friend void application::run();

	//start an window,only can be use in application::run()
	void _loadWindow();

	//save window
	GLFWwindow* _window;

public:
	//init rendermanager
	gl_manager()
	{
		glManagerInstance = this;
	}

	//get rendermanager instance
	static gl_manager& getInstance()
	{
		return *glManagerInstance;
	}
};