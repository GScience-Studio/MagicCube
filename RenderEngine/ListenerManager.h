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

	//window size change function
	virtual void windowsSizeChangeListener(int width, int height) {}

	//destructor
	virtual ~listener() {}
};

class listener_manager
{
	//key callback
	friend void keyboardCallback(GLFWwindow*, int, int, int, int);
	
	//cursor callback
	friend void cursorCallback(GLFWwindow*, double, double);

	//window size callback
	friend void windowsSizeChangeCallback(GLFWwindow*, int, int);

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
	//unregister listener and free memory
	void unregisterListenerAndFreeMemory(listener* inListener)
	{
		unregisterListener(inListener);

		delete(inListener);
	}

	//unregister listener but don't free memory
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
				//can I unregister this listener?
				if (_isCallingListener)
				{
					inListener = nullptr;

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