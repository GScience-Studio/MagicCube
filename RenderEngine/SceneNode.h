#pragma once

#include "RenderEngine.h"
#include "RenderNodeManager.h"
#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

void calculateFrustumPlanes(glm::dmat4& modleVerMatrix);

//scene
class scene_node :public render_node_manager
{
	friend class scene_node_manager;

private:
	//draw a scene
	void _draw(camera inGlobalCamera)
	{
		camera globalCamera = inGlobalCamera;

		glm::dmat4 cameraTranslate = glm::translate<double>(glm::dmat4(), glm::dvec3(-globalCamera.getLocation()->getX(), -globalCamera.getLocation()->getY(), -globalCamera.getLocation()->getZ()));
		glm::dmat4 cameraRotate = glm::rotate<double>(glm::dmat4(), -globalCamera.getAngle()->getPosX(), glm::dvec3(1.0, 0.0, 0.0)) * glm::rotate<double>(glm::dmat4(), -globalCamera.getAngle()->getPosY(), glm::dvec3(0.0, 1.0, 0.0));

		calculateFrustumPlanes(cameraRotate * cameraTranslate);

		//get render node list
		render_node_list renderNodeList = _getRenderNodeList();

		//check all render node
		for (auto& renderNode : renderNodeList)
		{
			renderNode->_draw(globalCamera);
		}
	}
public:
	virtual void onUnload() = 0;
	virtual void onLoad() = 0;
};