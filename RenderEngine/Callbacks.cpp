
#include "RenderEngine.h"
#include "ListenerManager.h"

//only can use in listener manager and callback
extern listener_manager* listenerManagerInstance;

/*
* keyboard callback
* made by GM2000
*/
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//lock and copy the list
	listenerManagerInstance->lock.lock();
	std::list<listener*> listenerList = listenerManagerInstance->_listenerList;
	listenerManagerInstance->lock.unlock();

	for (listener* getListener : listenerList)
	{
		if (getListener == nullptr)
			continue;

		getListener->keyListener(key, action);
	}

	//refresh listeners
	listenerManagerInstance->_refreshListeners();
}

/*
* window size change listener
* made by GM2000
*/
void windowsSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	//lock and copy the list
	listenerManagerInstance->lock.lock();
	std::list<listener*> listenerList = listenerManagerInstance->_listenerList;
	listenerManagerInstance->lock.unlock();

	for (listener* getListener : listenerList)
	{
		if (getListener == nullptr)
			continue;

		getListener->windowsSizeChangeListener(width, height);
	}

	//refresh listeners
	listenerManagerInstance->_refreshListeners();
}

/*
* tick refresh
* made by GM2000
*/
void tickListenerRefresh()
{
	//lock and copy the list
	listenerManagerInstance->lock.lock();
	std::list<listener*> listenerList = listenerManagerInstance->_listenerList;
	listenerManagerInstance->lock.unlock();

	for (listener* getListener : listenerList)
	{
		if (getListener == nullptr)
			continue;

		getListener->tickListener();
	}

	//refresh listeners
	listenerManagerInstance->_refreshListeners();
}

//save the last cursor location
double lastPosX = 0;
double lastPosY = 0;

/*
* cursor move callback

* made by GM2000
*/
void cursorCallback(GLFWwindow* window, double posX, double posY)
{
	//lock and copy the list
	listenerManagerInstance->lock.lock();
	std::list<listener*> listenerList = listenerManagerInstance->_listenerList;
	listenerManagerInstance->lock.unlock();

	for (listener* getListener : listenerList)
	{
		if (getListener == nullptr)
			continue;

		getListener->cursorListener(lastPosX, lastPosY, posX, posY);
	}

	lastPosX = posX;
	lastPosY = posY;

	//refresh listeners
	listenerManagerInstance->_refreshListeners();
}

/*
* framebuffer size change callback(this callback will no support register to listener)

* made by GM2000
*/
void framebufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

/*
* register and init all callback

* made by GM2000
*/
void initCallback(GLFWwindow* window)
{
	//init listener
	glfwGetCursorPos(window, &lastPosX, &lastPosY);

	//register callback
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeChangeCallback);
	glfwSetWindowSizeCallback(window, windowsSizeChangeCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
}