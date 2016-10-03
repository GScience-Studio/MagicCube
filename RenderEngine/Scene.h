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
};