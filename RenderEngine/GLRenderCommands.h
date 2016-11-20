#pragma once

#include "RenderEngine.h"

class buffer;
class render_program;

/*
* a command of set buffer data
* made by GM2000
*/
struct command_set_buffer_data
{
	buffer* inBuffer;
	const GLsizeiptr size;
	void* data;
	const unsigned int differentBufferDataPos;
	render_program* shaderProgram;

	command_set_buffer_data(buffer* inBuffer, const unsigned int differentBufferDataPos, const GLsizeiptr size, void* data, render_program* shaderProgram) :inBuffer(inBuffer), differentBufferDataPos(differentBufferDataPos), size(size), data(data), shaderProgram(shaderProgram) {}
};

/*
* render queue witch can be automatic add to renferqueue
* made by GM2000
*/
struct gl_render_command
{
	//command tyoe
	enum command_type
	{
		COMMAND_SET_BUFFER_DATA
	} commandType;

	//data
	void* data;

	gl_render_command(command_type commandType, void* data) :commandType(commandType), data(data) {}
};