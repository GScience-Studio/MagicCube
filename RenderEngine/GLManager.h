#pragma once

#include "RenderEngine.h"
#include "Application.h"

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

protected:
	//start an window,only can be use in application::run()
	void _loadWindow();

	//save window
	GLFWwindow* _window;	
	
	//gl instance
	static gl_manager _glInstance;

	//init rendermanager
	gl_manager()
	{
		//glInstance = this;
	}
public:
	//treate event
	void poolEvent()
	{
		glfwPollEvents();
	}
	//swap buffer
	void swapBuffers()
	{
		glfwSwapBuffers(_window);
	}
	//clear
	void clear(GLbitfield mask)
	{
		glClear(mask);
	}
	//stop and clear
	void terminate()
	{
		glfwTerminate();
	}
	//should close the window
	bool windowShouldClose()
	{
		return glfwWindowShouldClose(_window) == 1;
	}

	//get rendermanager instance
	static gl_manager& getInstance()
	{
		return _glInstance;
	}
};