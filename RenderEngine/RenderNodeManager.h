#pragma once

#include "RenderEngine.h"
#include "RenderNode.h"

typedef std::forward_list<render_node*> render_node_list;

//render node manager
class render_node_manager
{
private:
	//render node lock
	std::mutex lock;

	//save the list that gen in this scene
	render_node_list _renderNodeList;

protected:
	render_node_list _getRenderNodeList()
	{
		std::lock_guard<std::mutex> lockGuard(lock);

		return _renderNodeList;
	}

public:
	/*
	* add an render node by user
	* and auto sort by priority from height to less
	* made by GM2000
	*/
	render_node* addRenderNode(render_node* renderNode)
	{
		std::lock_guard<std::mutex> lockGuard(lock);

		render_node_list::const_iterator lastRenderNode = _renderNodeList.before_begin();

		for (render_node_list::const_iterator findHigherRenderNode = _renderNodeList.begin(); findHigherRenderNode != _renderNodeList.end(); findHigherRenderNode++)
		{
			if ((**findHigherRenderNode) > (*renderNode))
			{
				lastRenderNode = findHigherRenderNode;
			}
			else
			{
				_renderNodeList.emplace_after(lastRenderNode, renderNode);

				return renderNode;
			}
		}
		_renderNodeList.emplace_after(lastRenderNode, renderNode);

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