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
		//check all render node
		for (auto& renderNode : _renderNodeList)
		{
			renderNode->_draw(globalCamera);
		}
	}

public:
	//will call at each tick if the scene is enable
	virtual void sceneTickCall() {};
};