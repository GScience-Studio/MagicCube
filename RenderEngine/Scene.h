#pragma once

#include "RenderEngine.h"
#include "RenderNodeManager.h"

//scene
class scene :public render_node_manager
{
	friend class scene_manager;

private:
	//draw a scene
	void _draw()
	{
		//check all render node
		for (auto& renderNode : _renderNodeList)
		{
			renderNode->_draw();
		}
	}

public:
	~scene()
	{
		//free
		for (auto* renderNode : _renderNodeList)
		{
			delete(renderNode);
		}
	}
	//add an render node by user
	void addRenderNode(const render_node& renderNode)
	{
		_renderNodeList.push_front(new render_node(renderNode));
	}
	//add canvas
	canvas* addCanvas()
	{
		return _addCanvas();
	}
};