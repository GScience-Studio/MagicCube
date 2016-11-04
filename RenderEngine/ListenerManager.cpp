
#include "ListenerManager.h"

//only can uuse in listener manager
listener_manager* listenerManagerInstance;

//register callback
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->listenerList)
	{
		listenerList->keyListener(key, action);
	}

	listenerManagerInstance->_refreshListener();
}

//tick refresh
void tickListenerRefresh()
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->listenerList)
	{
		listenerList->tickListener();
	}

	listenerManagerInstance->_refreshListener();
}

//cursor move callback
double lastPosX = 0;
double lastPosY = 0;

void cursorCallback(GLFWwindow* window, double posX, double posY)
{
	for (listener* listenerList : listenerManagerInstance->listenerList)
	{
		listenerList->cursorListener(lastPosX, lastPosY, posX, posY);
	}

	listenerManagerInstance->_refreshListener();

	lastPosX = posX;
	lastPosY = posY;
}

//init listener manager(instance and callback)
void listener_manager::_initListenerManager(GLFWwindow* window)
{
	listenerManagerInstance = this;

	//init listener
	glfwGetCursorPos(window, &lastPosX, &lastPosY);

	//register callback
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
}