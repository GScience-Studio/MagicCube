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

	float lightVec[3]{ 0.0,0.0,0.0 };

	bool _setCameraAndCheckIsInSight(camera modelCamera)
	{
		render_location<double> modelLocation = *modelCamera.getLocation();

		if (!isCubeInFrustum(modelLocation.getX(), modelLocation.getY(), modelLocation.getZ(), modelLocation.getX() + 16.0f, modelLocation.getY() + 16.0f, modelLocation.getZ() + 16.0f))
			return false;

		gl_manager::getInstance().useShaderProgram(_programID);

		glm::dmat4 cameraTranslate = glm::translate<double>(glm::dmat4(), glm::dvec3(modelCamera.getLocation()->getX(), modelCamera.getLocation()->getY(), modelCamera.getLocation()->getZ()));

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(glm::mat4(globalMatrix * cameraTranslate)));

		return true;
	}

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera globalCamera, camera modelLocation)
	{
		if (_setCameraAndCheckIsInSight(modelLocation))
		{
			glInstance.useBuffer(buffer);
			glInstance.useShaderProgram(_programID);

			//block data
			glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint) * 2, (const void*)(sizeof(GLuint) * 0));
			glEnableVertexAttribArray(0);

			//nearby block info
			glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(GLuint) * 2, (const void*)(sizeof(GLuint) * 1));
			glEnableVertexAttribArray(1);

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