#pragma once

#include "GLManager.h"
#include "Canvas.h"

#include <forward_list>

typedef std::forward_list<render_node*> render_node_list;

class render_node_manager
{
private:
	gl_manager&	_glInstance = gl_manager::getInstance();

protected:
	canvas& _addCanvas(render_node_list& renderNodeList)
	{
		renderNodeList.push_front(new canvas());

		return (canvas&)renderNodeList.front();
	}
};