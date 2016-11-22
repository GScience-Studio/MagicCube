
#include "RenderEngine.h"
#include "InputCallbackManager.h"

//only can use in listener manager and callback
extern input_callback_manager* inputCallbackManagerInstance;

/*
* keyboard callback
* made by GM2000
*/
void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	inputCallbackManagerInstance->addEvent(KEYBOARD_EVENT, new keyboard_event(key, action));
}

/*
* window size change listener
* made by GM2000
*/
void windowsSizeChangeCallback(GLFWwindow* window, int width, int height)
{
	inputCallbackManagerInstance->addEvent(WINDOW_RESIZE_EVENT, new window_resize_event(width, height));
}

/*
* tick refresh
* made by GM2000
*/
void tickListenerRefresh()
{
	inputCallbackManagerInstance->lock.lock();

	//refresh input callback
	inputCallbackManagerInstance->_refreshInputCallbacks();

	//copy input callback
	std::list<input_callback*> inputCallbackList = inputCallbackManagerInstance->_inputCallbackList;

	inputCallbackManagerInstance->lock.unlock();

	//tick call
	for (input_callback* getInputCallback : inputCallbackList)
	{
		if (getInputCallback == nullptr)
			continue;

		getInputCallback->tickListener();
	}
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
	inputCallbackManagerInstance->addEvent(CURSOR_MOVE_EVENT, new cursor_move_event(posX, posY, lastPosX, lastPosY));

	lastPosX = posX;
	lastPosY = posY;
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