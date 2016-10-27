#pragma once

#include "RenderEngine.h"
#include "RenderNode.h"

typedef std::forward_list<render_node*> render_node_list;

//render node manager
class render_node_manager
{
protected:
	//save the list that gen in this scene
	render_node_list _renderNodeList;

public:
	//add an render node by user
	render_node* addRenderNode(render_node* renderNode)
	{
		_renderNodeList.push_front(renderNode);
		
		return renderNode;
	}
	~render_node_manager()
	{
		//free
		for (auto* renderNode : _renderNodeList)
		{
			delete(renderNode);
		}
	}
};