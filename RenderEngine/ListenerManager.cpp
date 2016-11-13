
#include "ListenerManager.h"

//only can uuse in listener manager
listener_manager* listenerManagerInstance;

//callback

/*keyboard callback*/
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->_listenerList)
	{
		if (listenerList == nullptr)
			continue;

		listenerList->keyListener(key, action);
	}

	listenerManagerInstance->_refreshListener();
}

/*window size change listener*/
void windowsSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->_listenerList)
	{
		if (listenerList == nullptr)
			continue;

		listenerList->windowsSizeChangeListener(width, height);
	}

	listenerManagerInstance->_refreshListener();
}

/*tick refresh*/
void tickListenerRefresh()
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->_listenerList)
	{
		if (listenerList == nullptr)
			continue;

		listenerList->tickListener();
	}

	listenerManagerInstance->_refreshListener();
}

/*cursor move callback*/

//save the last cursor location
double lastPosX = 0;
double lastPosY = 0;

//callback
void cursorCallback(GLFWwindow* window, double posX, double posY)
{
	if (listenerManagerInstance == nullptr)
		return;

	for (listener* listenerList : listenerManagerInstance->_listenerList)
	{
		listenerList->cursorListener(lastPosX, lastPosY, posX, posY);
	}

	listenerManagerInstance->_refreshListener();

	lastPosX = posX;
	lastPosY = posY;
}

/*input chars callback*/
void characterCallback(GLFWwindow* window, unsigned int codepoint)
{
	//recieve data
	std::wcout << "recieve: " << (wchar_t)codepoint << std::endl;

	//treate listener
	for (listener* listenerList : listenerManagerInstance->_listenerList)
	{

		//listenerList->charInputCallback(getChar);
	}
	listenerManagerInstance->_refreshListener();
}
//framebuffer size change callback(this callback will no support register to listener)
void framebufferSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//init listener manager(instance and callback)
void listener_manager::_initListenerManager(GLFWwindow* window)
{
	listenerManagerInstance = this;

	//init listener
	glfwGetCursorPos(window, &lastPosX, &lastPosY);

	//register callback
	glfwSetKeyCallback(window, keyboardCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeChangeCallback);
	glfwSetWindowSizeCallback(window, windowsSizeChangeCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetCharCallback(window, characterCallback);
}