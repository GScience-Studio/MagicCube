
#include "EventQueue.h"
#include "InputCallbackManager.h"

extern input_callback_manager* inputCallbackManagerInstance;

void event_queue::addEvent(event_type eventType, void* data)
{
	_lock.lock();

	_eventQueue.push({ eventType ,data });

	_lock.unlock();
}
void event_queue::refreshEvent()
{
	//copy and clear the queue
	_lock.lock();

	std::queue<std::pair<event_type, void*>> eventQueue = _eventQueue;
	_eventQueue.swap(std::queue<std::pair<event_type, void*>>());

	_lock.unlock();

	while (eventQueue.size() != 0)
	{
		//read one event
		auto getEvent = eventQueue.front();

		eventQueue.pop();

		//callback
		switch (getEvent.first)
		{
		case KEYBOARD_EVENT:
		{
			//lock and copy the callback list
			inputCallbackManagerInstance->lock.lock();

			//refresh listeners
			inputCallbackManagerInstance->_refreshInputCallbacks();

			std::list<input_callback*> inputCallbackList = inputCallbackManagerInstance->_inputCallbackList;

			inputCallbackManagerInstance->lock.unlock();

			//get event data
			keyboard_event* keyboardEvent = (keyboard_event*)getEvent.second;

			//call
			for (input_callback* getInputCallback : inputCallbackList)
			{
				if (getInputCallback == nullptr)
					continue;

				getInputCallback->keyListener(keyboardEvent->key, keyboardEvent->action);
			}
			//free memory
			delete (keyboardEvent);

			break;
		}
		case CURSOR_MOVE_EVENT:
		{
			//lock and copy the callback list
			inputCallbackManagerInstance->lock.lock();

			//refresh listeners
			inputCallbackManagerInstance->_refreshInputCallbacks();

			std::list<input_callback*> inputCallbackList = inputCallbackManagerInstance->_inputCallbackList;

			inputCallbackManagerInstance->lock.unlock();

			//get event data
			cursor_move_event* cursorMoveEvent = (cursor_move_event*)getEvent.second;

			//call
			for (input_callback* getInputCallback : inputCallbackList)
			{
				if (getInputCallback == nullptr)
					continue;

				getInputCallback->cursorListener(cursorMoveEvent->lastPosX, cursorMoveEvent->lastPosY, cursorMoveEvent->posX, cursorMoveEvent->posY);
			}
			//free memory
			delete (cursorMoveEvent);

			break;
		}
		case WINDOW_RESIZE_EVENT:
		{
			//lock and copy the callback list
			inputCallbackManagerInstance->lock.lock();

			//refresh listeners
			inputCallbackManagerInstance->_refreshInputCallbacks();

			std::list<input_callback*> inputCallbackList = inputCallbackManagerInstance->_inputCallbackList;

			inputCallbackManagerInstance->lock.unlock();

			//get event data
			window_resize_event* windowResizeEvent = (window_resize_event*)getEvent.second;

			//call
			for (input_callback* getInputCallback : inputCallbackList)
			{
				if (getInputCallback == nullptr)
					continue;

				getInputCallback->windowsSizeChangeListener(windowResizeEvent->width, windowResizeEvent->height);
			}
			//free memory
			delete (windowResizeEvent);

			break;
		}
		}
	}
}