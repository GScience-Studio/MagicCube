#pragma once

#include <algorithm>
#include "RenderEngine.h"

class listener
{
	friend class listener_manager;

private:
	//listener's ID
	std::forward_list<listener*>::iterator listenerID;

public:
	//keyboard function
	virtual void keyListener(int key, int action) {}
	
	//tick function
	virtual void tickListener() {}
};

class listener_manager
{
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void tickListenerRefresh();

private:
	std::forward_list<listener*> listenerList;

protected:
	void _initListenerManager(GLFWwindow* window);

public:
	void registerListener(listener* listener)
	{
		listenerList.push_front(listener);
		listener->listenerID = listenerList.begin();
	}

	void unregisterListener(listener* listener)
	{
		listenerList.erase_after(listener->listenerID);
	}
};