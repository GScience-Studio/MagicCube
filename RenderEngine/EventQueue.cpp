
#include "EventQueue.h"
#include "InputCallbackManager.h"

extern input_callback_manager* inputCallbackManagerInstance;

void event_queue::addEvent(event_type eventType, void* data)
{
	_lock.lock();

	_eventQueue.push_front({ eventType ,data });

	_lock.unlock();
}
void event_queue::refreshEvent()
{
	_lock.lock();

	std::forward_list<std::pair<event_type, void*>> eventQueue = _eventQueue;

	_eventQueue.clear();

	_lock.unlock();

	for (auto getEvent : eventQueue)
	{
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
		}
	}
}