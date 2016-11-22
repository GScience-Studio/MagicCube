#pragma once

#include "RenderEngine.h"

#include <queue>

enum event_type
{
	CURSOR_MOVE_EVENT, WINDOWS_SIZE_CHANGE_EVENT, KEYBOARD_EVENT, WINDOW_RESIZE_EVENT
};

class event_queue
{
private:
	std::mutex _lock;

	std::queue<std::pair<event_type, void*>> _eventQueue;

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
struct window_resize_event
{
	int width;
	int height;

	window_resize_event(int width, int height) :width(width), height(height) {}
};
struct cursor_move_event
{
	double posX;
	double posY;

	double lastPosX;
	double lastPosY;

	cursor_move_event(double posX, double posY, double lastPosX, double lastPosY) :posX(posX), posY(posY), lastPosX(lastPosX), lastPosY(lastPosY) {}
};