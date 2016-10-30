
#include "ListenerManager.h"

listener_manager* listenerManagerInstance;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (listenerManagerInstance == nullptr)
		return;

	for (key_listener keyListener : listenerManagerInstance->keyListenerList)
	{
		keyListener(key, action);
	}
}

void listenerTickRefresh()
{
	if (listenerManagerInstance == nullptr)
		return;

	for (tick_listener tickListener : listenerManagerInstance->tickListenerList)
	{
		tickListener();
	}
}
void listener_manager::_initListenerManager(GLFWwindow* window)
{
	listenerManagerInstance = this;

	glfwSetKeyCallback(window, keyCallback);
}