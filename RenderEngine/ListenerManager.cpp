
#include "ListenerManager.h"

//only can use in listener manager and callback
listener_manager* listenerManagerInstance;

/*
* register and init all callback
* made by GM2000
*/
void initCallback(GLFWwindow* window);

/*
unregister listener but don't free memory

thread-safety: can be use in all thread

made by GM2000
*/
void listener_manager::unregisterListener(listener* inListener)
{
	//whether it is an unable listener
	if (inListener == nullptr)
		return;

	listenerManagerInstance->lock.lock();

	//find and delete listener
	for (auto findObject = _listenerList.begin(); findObject != _listenerList.end(); findObject++)
	{
		//is listener?
		if (*findObject == inListener)
		{
			listenerManagerInstance->lock.unlock();

			//can I unregister this listener?
			if (_isCallingListener)
			{
				inListener = nullptr;

				_unregisterListenerList.push_front(findObject);

				return;
			}

			//remove
			_listenerList.erase(findObject);

			return;
		}
	}

	listenerManagerInstance->lock.unlock();
}

/*
unregister listener and free memory

thread-safety: can be use in all thread

warning:make sure that your listener can be delete

made by GM2000
*/
void listener_manager::unregisterListenerAndFreeMemory(listener* inListener)
{
	unregisterListener(inListener);

	delete(inListener);
}

/*
* register an new listener.please use new to allocate memory to listener

* thread-safety: can be use in all thread

* made by GM2000
*/
listener* listener_manager::registerListener(listener* inListener)
{
	//whether it is an unable listener
	if (inListener == nullptr)
		return nullptr;

	listenerManagerInstance->lock.lock();
	
	//get thread ID
	inListener->_threadID = std::this_thread::get_id();

	//register it
	_listenerList.push_front(inListener);

	listenerManagerInstance->lock.unlock();

	return inListener;
}

/*
* remove listener which had been unregister by user

* thread-safety: can be use in all thread

* made by GM2000
*/
void listener_manager::_refreshListeners()
{
	listenerManagerInstance->lock.lock();

	for (auto findObject : _unregisterListenerList)
	{
		_listenerList.erase(findObject);
	}

	listenerManagerInstance->lock.unlock();
}

/*
* init listener manager(instance and callback)

* warning: user shouldn't call this function except
* they know what are you doing

* made by GM2000
*/
void listener_manager::_initListenerManager(GLFWwindow* window)
{
	listenerManagerInstance = this;

	initCallback(window);
}