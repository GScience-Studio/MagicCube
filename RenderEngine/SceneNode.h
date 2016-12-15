#pragma once

#include "RenderEngine.h"
#include "RenderNodeManager.h"
#include "Camera.h"

#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

void calculateFrustumPlanes(glm::mat4& modleVerMatrix);

//scene
class scene_node :public render_node_manager
{
	friend class scene_node_manager;

private:
	//draw a scene
	void _draw(camera_synchronize globalCamera)
	{
		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(-globalCamera.getLocation()->getX(), globalCamera.getLocation()->getY(), -globalCamera.getLocation()->getZ()));
		glm::mat4 cameraRotate = glm::rotate(glm::mat4(), globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

		calculateFrustumPlanes(cameraRotate * cameraTranslate);

		//get render node list
		render_node_list renderNodeList = _getRenderNodeList();

		//check all render node
		for (auto& renderNode : renderNodeList)
		{
			renderNode->_draw(globalCamera);
		}
	}
};