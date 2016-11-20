#pragma once

#include "GLManager.h"

extern render_program* chunkRenderProgram;

class chunk_render_program :public render_program
{
private:
	gl_manager& glInstance = gl_manager::getInstance();

	//light location
	GLuint _lightPosLocation;
	//eyes location
	GLuint _eyesPosLocation;

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera& globalCamera, camera& modelLocation)
	{
		glInstance.useBuffer(buffer);
		glInstance.useShaderProgram(_programID);

		_setCamera(globalCamera, modelLocation);

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
		float lightVec[]{ x,y,z };

		glUniform3fv(_lightPosLocation, 1, lightVec);
	}

	void setEyes(float x, float y, float z)
	{
		float eyesVec[]{ x,y,z };

		glUniform3fv(_eyesPosLocation, 1, eyesVec);
	}
};