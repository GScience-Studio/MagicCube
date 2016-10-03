#pragma once

#include "RenderEngine.h"
#include "Canvas.h"
#include "RenderNode.h"

typedef std::forward_list<render_node*> render_node_list;

//render node manager
class render_node_manager
{
protected:
	//save the list that gen in this scene
	render_node_list _renderNodeList;

public:
	canvas* addCanvas()
	{
		_renderNodeList.push_front(new canvas());

		return (canvas*)_renderNodeList.front();
	}
	//add an render node by user
	void addRenderNode(render_node* renderNode)
	{
		_renderNodeList.push_front(renderNode);
	}
};