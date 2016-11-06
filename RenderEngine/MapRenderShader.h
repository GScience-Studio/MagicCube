#pragma once

#include "GLManager.h"

extern shader_program* mapRenderShader;

class map_render_shader :public shader_program
{
private:
	gl_manager& glInstance = gl_manager::getInstance();

	//draw
	void _draw(const GLint first, const GLsizei count) const
	{
		glDrawArrays(GL_POINTS, first, count);
	}
	void _init()
	{
		glUniform1i(glGetUniformLocation(_programID, "texture"), 0);
		glUniform1i(glGetUniformLocation(_programID, "normal"), 1);
	}
public:
	//create buffer by daat
	void setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const;
};