
#include "InputCallbackManager.h"

//only can use in listener manager and callback
input_callback_manager* inputCallbackManagerInstance;

/*
* register and init all callback
* made by GM2000
*/
void initCallback(GLFWwindow* window);

void input_callback_manager::unregisterInputCallback(input_callback* inputCallback)
{
	//whether it is an unable listener
	if (inputCallback == nullptr)
		return;

	inputCallbackManagerInstance->lock.lock();

	//find and delete listener
	for (auto findObject = _inputCallbackList.begin(); findObject != _inputCallbackList.end(); findObject++)
	{
		//is listener?
		if (*findObject == inputCallback)
		{
			inputCallbackManagerInstance->lock.unlock();

			//can I unregister this listener?
			if (_isCallingListener)
			{
				_unregisterInputCallbackList.push_front(findObject);

				return;
			}

			//remove
			_inputCallbackList.erase(findObject);

			return;
		}
	}

	inputCallbackManagerInstance->lock.unlock();
}

input_callback* input_callback_manager::registerInputCallback(input_callback* inputCallback)
{
	//whether it is an unable listener
	if (inputCallback == nullptr)
		return nullptr;

	inputCallbackManagerInstance->lock.lock();
	
	//register it
	_inputCallbackList.push_front(inputCallback);

	inputCallbackManagerInstance->lock.unlock();

	return inputCallback;
}

void input_callback_manager::_refreshInputCallbacks()
{
	for (auto findObject : _unregisterInputCallbackList)
	{
		_inputCallbackList.erase(findObject);
	}
}

void input_callback_manager::_initInputCallbackManager(GLFWwindow* window)
{
	inputCallbackManagerInstance = this;

	initCallback(window);
}