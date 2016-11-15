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
	//add an render node by user
	render_node* addRenderNode(render_node* renderNode)
	{
		lock.lock();

		_renderNodeList.push_front(renderNode);
		
		lock.unlock();

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