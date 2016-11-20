#pragma once

#include "RenderEngine.h"
#include "EventQueue.h"
#include "InputCallback.h"

#include <list>

class input_callback_manager : protected event_queue
{
	//key callback
	friend void keyboardCallback(GLFWwindow*, int, int, int, int);
	
	//cursor callback
	friend void cursorCallback(GLFWwindow*, double, double);

	//window size callback
	friend void windowsSizeChangeCallback(GLFWwindow*, int, int);

	//tick refresh
	friend void tickListenerRefresh();

	friend class event_queue;
private:
	//listener list
	std::list<input_callback*> _inputCallbackList;

	//has refreshing listener?
	std::forward_list<std::list<input_callback*>::iterator> _unregisterInputCallbackList;

	//is refreshing listener?
	bool _isCallingListener = false;

	/*
	* remove listener which had been unregister by user

	* thread-safety: can be use in any thread but you should look

	* made by GM2000
	*/
	void _refreshInputCallbacks();

protected:
	/*
	* register an new listener.please use new to allocate memory to listener

	* thread-safety: only can use

	* made by GM2000
	*/
	void _initInputCallbackManager(GLFWwindow* window);

public:
	//thread lock
	std::mutex lock;

	/*
	* register an new listener.please use new to allocate memory to listener

	* thread-safety: can be use in all thread

	* made by GM2000
	*/
	input_callback* registerInputCallback(input_callback* inListener);

	/*
	* unregister listener but don't free memory

	* thread-safety: can be use in all thread

	* made by GM2000
	*/
	void unregisterInputCallback(input_callback* inListener);
};