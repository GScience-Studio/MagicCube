#pragma once

#include "RenderEngine.h"
#include "RenderNodeManager.h"
#include "Camera.h"

//scene
class scene :public render_node_manager
{
	friend class scene_manager;

private:
	//draw a scene
	void _draw(camera globalCamera)
	{
		//check all render node
		for (auto& renderNode : _renderNodeList)
		{
			renderNode->_draw(globalCamera);
		}
	}
};