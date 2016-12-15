#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

//glm
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

extern render_program* normal2DRenderProgram;
extern render_program* normal3DRenderProgram;

class normal_3d_render_program :public render_program
{
private:
	gl_manager& glInstance = gl_manager::getInstance();

	//draw
	void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera_synchronize& globalCamera, camera_synchronize& modelLocation)
	{
		glInstance.useBuffer(buffer);
		glInstance.useShaderProgram(_programID);

		_setCamera(globalCamera, modelLocation);

		glDrawArrays(GL_TRIANGLES, first, count);
	}
	void _init()
	{
		glUniform1i(glGetUniformLocation(_programID, "texture"), 0);
	}
public:
	//create buffer by daat
	void _setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const;
};

class normal_2d_render_program :public normal_3d_render_program
{
public:
	void setCamera(camera_synchronize& globalCamera, camera_synchronize& modelCamera) const
	{
		glm::mat4 cameraTranslate = glm::translate(glm::mat4(), glm::vec3(modelCamera.getLocation()->getX(), modelCamera.getLocation()->getY(), modelCamera.getLocation()->getZ()));

		glUniformMatrix4fv(_projection, 1, GL_TRUE, glm::value_ptr(cameraTranslate));
	}
};