#pragma once

#include "RenderEngine.h"
#include "RenderManager.h"
#include "RenderNode.h"

#include <forward_list>

class screen
{
	//save the list that gen in this screen
	std::forward_list<render_node> _renderNodeList;

public:
	//draw a screen
	void draw();

	//add an render node
	void addRenderNode(const render_node& renderNode)
	{
		_renderNodeList.push_front(renderNode);
	}
};
class screen_manager:public render_manager
{
	//get the screen now is shown or will be hide
	screen _getNowScreen();

	//get the screen that will be show after transition
	screen _getNextScreen();

public:
	//add an screen
	screen addScreen();

	//show an screen
	void showScreen();
};