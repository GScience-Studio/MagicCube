#pragma once

#include "RenderEngine.h"
#include "SceneManager.h"
#include "ListenerManager.h"
#include "ExtensionManager.h"

//app instance
class	application;
extern	application* applicationInstance;

/*
applicaion
The base class of a program.
It's a listener and it also is a listener manager.
So in there you can add your own listener function and register or unregister listener.
And it's also a scene manager witch can add and remove scene.
You can add more thing by extension such as shader and new kind of render node(some of them it's not necessary to add by extension manager)
*/
class application :public scene_manager, public listener_manager, public extension_manager, public listener
{
	friend class listener_manager;

protected:
	//application base info
	const char*		_appName;
	const char*		_version;

	size_vec	_windowSize;

private:
	//gl instance
	gl_manager& _glInstance = gl_manager::getInstance();

	//main loop
	void _mainLoop();

	//refresh(a tick is 0.01s)
	void _tickRefresh(bool draw, bool refresh);

	//size change event
	void windowsSizeChangeListener(int width, int height) final
	{
		_windowSize.setWidth(width);
		_windowSize.setHeight(height);
	}
public:
	//cursor info
	bool isCursorEnable = true;

	application(const char* appName, const char* version, const size_vec& windowSize) :_appName(appName), _version(version), _windowSize(windowSize)
	{
		applicationInstance = this;

		registerListener(this);
	}

	//gen texture
	texture genTexture(std::initializer_list<const char*> fileName, GLuint count)
	{
		return _glInstance.genTexture((const char**)fileName.begin(), count);
	}
	texture genTexture(const char* fileName[], GLuint count)
	{
		return _glInstance.genTexture(fileName, count);
	}
	//init
	virtual void init() = 0;

	//get instance
	static application& getInstance()
	{
		return *applicationInstance;
	}
	
	//run program
	void run();

	//set cursor input mode
	void hideCursor()
	{
		isCursorEnable = false;

		glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void showCursor()
	{
		isCursorEnable = true;

		glfwSetInputMode(_glInstance._window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
};