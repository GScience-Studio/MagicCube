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

	void _setCamera(camera globalCamera, camera modelCamera)
	{
		location<double> modelLocation = *modelCamera.getLocation();

		isInSight = isCubeInFrustum((float)modelLocation.getX(), (float)modelLocation.getY(), (float)modelLocation.getZ(), (float)modelLocation.getX() + 16.0f, (float)modelLocation.getY() + 16.0f, (float)modelLocation.getZ() + 16.0f);

		if (!isInSight)
			return;

		gl_manager::getInstance().useShaderProgram(_programID);

		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(modelCamera.getLocation()->getX(), modelCamera.getLocation()->getY(), modelCamera.getLocation()->getZ()));

		glm::mat4 projection = glm::mat4(globalMatrix[0], globalMatrix[1], globalMatrix[2], globalMatrix[3],
			globalMatrix[4], globalMatrix[5], globalMatrix[6], globalMatrix[7],
			globalMatrix[8], globalMatrix[9], globalMatrix[10], globalMatrix[11],
			globalMatrix[12], globalMatrix[13], globalMatrix[14], globalMatrix[15]);

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(projection * cameraTranslate));
	}

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera globalCamera, camera modelLocation)
	{
		_setCamera(globalCamera, modelLocation);

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