#pragma once

#include <algorithm>
#include <list>

#include "RenderEngine.h"

class listener
{
	friend class listener_manager;

public:
	//keyboard function
	virtual void keyListener(int key, int action) {}
	
	//tick function
	virtual void tickListener() {}

	//cursor listener function
	virtual void cursorListener(double lastPosX, double lastPosY, double posX, double posY) {}

	//destructor
	virtual ~listener() {}
};

class listener_manager
{
	//key callback
	friend void keyCallback(GLFWwindow*, int, int, int, int);
	
	//cursor callback
	friend void cursorCallback(GLFWwindow*, double, double);

	//tick refresh
	friend void tickListenerRefresh();

private:
	//listener list
	std::list<listener*> listenerList;

	//has refreshing listener?
	std::forward_list<std::list<listener*>::iterator> unregisterListenerList;

	//is refreshing listener?
	bool _isCallingListener = false;

	//remove listener which had been unregister by user
	void _refreshListener()
	{
		for (auto findObject : unregisterListenerList)
		{
			listenerList.erase(findObject);
		}
	}
protected:
	//init function
	void _initListenerManager(GLFWwindow* window);

public:
	//register an new listener.please use new to allocate memory to listener
	listener* registerListener(listener* inListener)
	{
		//whether it is an unable listener
		if (inListener == nullptr)
			return nullptr;

		//register it
		listenerList.push_front(inListener);

		return inListener;
	}

	//unregister listener and auto free its memory
	void unregisterListener(listener* inListener)
	{
		//whether it is an unable listener
		if (inListener == nullptr)
			return;

		//find and delete listener
		for (auto findObject = listenerList.begin(); findObject != listenerList.end(); findObject++)
		{
			//is listener?
			if (*findObject == inListener)
			{
				//set it to null and free its memory
				*findObject = nullptr;

				delete(inListener);

				//can I unregister this listener?
				if (_isCallingListener)
				{
					unregisterListenerList.push_front(findObject);

					return;
				}

				//remove
				listenerList.erase(findObject);

				return;
			}
		}
	}
};