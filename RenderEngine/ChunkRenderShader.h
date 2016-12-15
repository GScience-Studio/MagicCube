#pragma once

#include "GLManager.h"
#include "Fusum.h"

//glm
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

extern render_program* chunkRenderProgram;

class chunk_render_program :public render_program
{
private:
	gl_manager& glInstance = gl_manager::getInstance();

	//light location
	GLuint _lightPosLocation;

	//light lock
	std::mutex lightLock;

	//eyes location
	GLuint _eyesPosLocation;

	//is in player sight?
	bool isInSight = false;

	float lightVec[3]{ 0.0,0.0,0.0 };

	void _setCamera(camera_synchronize& globalCamera, camera_synchronize& modelLocation)
	{
		gl_manager::getInstance().useShaderProgram(_programID);

		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(modelLocation.getLocation()->getX() -globalCamera.getLocation()->getX(), modelLocation.getLocation()->getY() -globalCamera.getLocation()->getY(), modelLocation.getLocation()->getZ() -globalCamera.getLocation()->getZ()));
		glm::mat4 cameraRotate = glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

		isInSight = isCubeInFrustum((float)modelLocation.getLocation()->getX(), (float)modelLocation.getLocation()->getY(), (float)modelLocation.getLocation()->getZ(), (float)modelLocation.getLocation()->getX() + 16.0f, (float)modelLocation.getLocation()->getY() + 16.0f, (float)modelLocation.getLocation()->getZ() + 16.0f);

		if (!isInSight)
			return;

		glm::mat4 projection = gl_manager::getInstance().getPerspective() * cameraRotate * cameraTranslate;

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(projection));
	}

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera_synchronize& globalCamera, camera_synchronize& modelLocation)
	{
		_setCamera(globalCamera, modelLocation);

		//check whether the chunk is in player's sight
		
		//set light(can't use now)
		/*
		if (lightLock.try_lock())
		{
			glUniform3fv(_lightPosLocation, 1, lightVec);

			lightLock.unlock();
		}
		*/

		if (isInSight)
		{
			glInstance.useBuffer(buffer);
			glInstance.useShaderProgram(_programID);

			glDrawArrays(GL_POINTS, first, count);
		}
	}

	//init
	void _init()
	{
		//set texture
		glUniform1i(glGetUniformLocation(_programID, "texture"), 0);
		glUniform1i(glGetUniformLocation(_programID, "normal"), 1);
		glUniform1i(glGetUniformLocation(_programID, "depthMap"), 2);

		//get light location
		_lightPosLocation = glGetUniformLocation(_programID, "lightPos");
		_eyesPosLocation = glGetUniformLocation(_programID, "eyesPos");
	}
	//create buffer by daat
	void _setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const;

public:
	/*set light pos
	from the input location to 0,0,0
	*/
	void setLight(float x, float y, float z)
	{
		lightLock.lock();

		lightVec[0] = x;
		lightVec[1] = y;
		lightVec[2] = z;

		lightLock.unlock();
	}
};