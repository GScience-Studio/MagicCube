
#include "Application.h"
#include "RenderManager.h"

application* applicationInstance;

void application::run()
{
	//call init
	init();

	//init renderManagerInstance
	render_manager();

	//load window
	render_manager::getInstance()._loadWindow();
}