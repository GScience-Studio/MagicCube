
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
}

//init listener manager(instance and callback)
void listener_manager::_initListenerManager(GLFWwindow* window)
{
	listenerManagerInstance = this;

	glfwSetKeyCallback(window, keyCallback);
}