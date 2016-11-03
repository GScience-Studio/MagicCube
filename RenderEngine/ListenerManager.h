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

	//destructor
	virtual ~listener() {}
};

class listener_manager
{
	//call back
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void tickListenerRefresh();

private:
	//listener list
	std::list<listener*> listenerList;

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
				//remove
				listenerList.erase(findObject);

				delete(inListener);

				return;
			}
		}
	}
};