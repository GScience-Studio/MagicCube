#pragma once

#include "RenderEngine.h"
#include <functional>

/*键盘监听函数
  key为用户所发送的按键
  action为用户的具体操作*/
typedef std::function<void(int key,int action)> key_listener;

class listener_manager
{
	friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	std::vector<key_listener> keyListenerList;

protected:
	void _initListenerManager(GLFWwindow* window);

public:
	void registerListener(key_listener keyListener)
	{
		keyListenerList.push_back(keyListener);
	}
};