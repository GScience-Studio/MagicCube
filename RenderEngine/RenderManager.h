#pragma once

#include "RenderEngine.h"
#include "Application.h"

//save the instance
class	render_manager;
extern	render_manager* renderManagerInstance;

//rendermanager
class render_manager
{
	friend class application;

	//start an window
	void _loadWindow();

	//save window
	GLFWwindow* _window;

public:
	//init rendermanager
	render_manager()
	{
		renderManagerInstance = this;
	}

	//get rendermanager instance
	static render_manager& getInstance()
	{
		return *renderManagerInstance;
	}
};