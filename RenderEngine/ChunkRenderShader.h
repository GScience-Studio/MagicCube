#pragma once

#include "GLManager.h"

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

	bool _isPointInSight(glm::mat4& projection, glm::vec4& location)
	{
		location = location * projection;

		location /= location.w;

		if ((location.x > 2.0f || location.x < -1.0f) ||
			(location.y > 2.0f || location.y < -1.0f))
			return false;
		else
			return true;
	}

	void _setCamera(camera& globalCamera, camera& modelLocation)
	{
		gl_manager::getInstance().useShaderProgram(_programID);

		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(-globalCamera.getLocation()->getX(), -globalCamera.getLocation()->getY(), -globalCamera.getLocation()->getZ()));
		glm::mat4 cameraRotate = glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), -globalCamera.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 cameraModelTranslate = glm::translate(glm::mat4(), glm::vec3(modelLocation.getLocation()->getX(), modelLocation.getLocation()->getY(), modelLocation.getLocation()->getZ()));
		glm::mat4 cameraModelRotate = glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosX(), glm::vec3(1.0, 0.0, 0.0)) * glm::rotate(glm::mat4(), modelLocation.getAngle()->getPosY(), glm::vec3(0.0, 1.0, 0.0));

		glm::mat4 projection = gl_manager::getInstance().getPerspective() * cameraRotate * cameraTranslate * cameraModelTranslate * cameraModelRotate;

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(projection));
	}

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera& globalCamera, camera& modelLocation)
	{
		glInstance.useBuffer(buffer);
		glInstance.useShaderProgram(_programID);

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
		glDrawArrays(GL_POINTS, first, count);
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