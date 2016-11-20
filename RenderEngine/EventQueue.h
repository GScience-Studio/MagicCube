#pragma once

#include "RenderEngine.h"

enum event_type
{
	CURSOR_MOVE_EVENT, WINDOWS_SIZE_CHANGE_EVENT, TICK_EVENT, KEYBOARD_EVENT
};

class event_queue
{
private:
	std::mutex _lock;

	std::forward_list<std::pair<event_type, void*>> _eventQueue;

public:
	/*
	* add event
	* thread-safety: can be use in all thread
	* made by GM2000
	*/
	void addEvent(event_type eventType, void* data);

	/*
	* refresh event
	* made by GM2000
	*/
	void event_queue::refreshEvent();
};

struct keyboard_event
{
	int key;
	int action;

	keyboard_event(int key, int action) :key(key), action(action) {}
};
struct cursor_move_event
{
	int posX;
	int posY;

	int lastPosX;
	int lastPosY;

	cursor_move_event(int posX, int posY, int lastPosX, int lastPosY) :posX(posX), posY(posY), lastPosX(lastPosX), lastPosY(lastPosY) {}
};