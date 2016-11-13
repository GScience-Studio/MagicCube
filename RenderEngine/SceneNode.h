#pragma once

#include "RenderEngine.h"
#include "RenderNodeManager.h"
#include "Camera.h"

//scene
class scene_node :public render_node_manager
{
	friend class scene_node_manager;

private:
	//draw a scene
	void _draw(camera globalCamera)
	{
		//get render node list
		render_node_list renderNodeList = _getRenderNodeList();

		//check all render node
		for (auto& renderNode : renderNodeList)
		{
			renderNode->_refreshData();
			renderNode->_draw(globalCamera);
		}
	}
};