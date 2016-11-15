#pragma once

#include "RenderEngine.h"
#include "EventPool.h"
#include "Listener.h"

#include <algorithm>
#include <list>

class listener_manager: protected event_pool
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
	std::list<listener*> _listenerList;

	//has refreshing listener?
	std::forward_list<std::list<listener*>::iterator> _unregisterListenerList;

	//is refreshing listener?
	bool _isCallingListener = false;

	//thread ID(to automatic register thread)
	const std::thread::id mainThreadID = std::this_thread::get_id();

	/*
	* remove listener which had been unregister by user

	* thread-safety: can be use in any thread

	* made by GM2000
	*/
	void _refreshListeners();

protected:
	/*
	* register an new listener.please use new to allocate memory to listener

	* thread-safety: only can use

	* made by GM2000
	*/
	void _initListenerManager(GLFWwindow* window);

	//thread lock
	std::mutex lock;
public:
	/*
	* register an new listener.please use new to allocate memory to listener

	* thread-safety: can be use in all thread

	* made by GM2000
	*/
	listener* registerListener(listener* inListener);

	/*
	* unregister listener and free memory

	* thread-safety:c an be use in all thread

	* warning:make sure that your listener can be delete

	* made by GM2000
	*/
	void unregisterListenerAndFreeMemory(listener* inListener);

	/*
	* unregister listener but don't free memory

	* thread-safety: can be use in all thread

	* made by GM2000
	*/
	void unregisterListener(listener* inListener);
};