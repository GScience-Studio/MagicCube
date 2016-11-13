#pragma once

#include "RenderEngine.h"

class event_pool
{
	enum event_type
	{
		CURSOR_MOVE_EVENT, WINDOWS_SIZE_CHANGE_EVENT, TICK_EVENT, KEYBOARD_EVENT
	};
public:
	/*add event
	thread-safety: can be use in all thread
	made by GM2000
	*/
	void addEvent(event_type Event);
};