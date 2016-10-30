#pragma once

#include "RenderEngine.h"
#include <functional>

/*���̼�������
  keyΪ�û������͵İ���
  actionΪ�û��ľ������*/
typedef std::function<void(int key, int action)> key_listener;
typedef std::function<void()> tick_listener;

class listener_manager
{
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	friend void listenerTickRefresh();

private:
	std::vector<key_listener>	keyListenerList;
	std::vector<tick_listener>	tickListenerList;

protected:
	void _initListenerManager(GLFWwindow* window);

public:
	void registerListener(key_listener keyListener)
	{
		keyListenerList.push_back(keyListener);
	}
	void registerListener(tick_listener tickListener)
	{
		tickListenerList.push_back(tickListener);
	}
};