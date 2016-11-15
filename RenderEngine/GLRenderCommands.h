#pragma once

#include "RenderEngine.h"

struct buffer
{
	//save buffer ID
	GLuint vao = 0;
	GLuint vbo = 0;

	//buffer size
	GLsizeiptr	size = 0;

	//has init
	bool	hasInit = false;

	buffer() {}

	buffer(GLuint vaoID, GLuint vboID) :vao(vaoID), vbo(vboID) {}

	//is equal
	bool operator ==(buffer buffer)
	{
		return vao == buffer.vao && vbo == buffer.vbo;
	}
};

//please use new,all funtion there will be called in main thread except the funtion you create
class shader_program
{
	friend class gl_manager;

private:
	virtual void _draw(const GLint first, const GLsizei count) const = 0;
	virtual void _init() = 0;

	virtual void _setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const = 0;
protected:
	GLuint _projection = 0;
	GLuint _programID = 0;

public:
	virtual void setCamera(camera& globalCamera, camera& modelLocation) const;
};

/*
* a command of set buffer data
* made by GM2000
*/
struct command_set_buffer_data
{
	buffer& inBuffer;
	const GLsizeiptr size;
	void* data;
	const unsigned int differentBufferDataPos;
	shader_program* shaderProgram;

	command_set_buffer_data(buffer& inBuffer, const unsigned int& differentBufferDataPos, const GLsizeiptr& size, void* data, shader_program* shaderProgram) :inBuffer(inBuffer), differentBufferDataPos(differentBufferDataPos), size(size), data(data), shaderProgram(shaderProgram) {}
};

/*
* a command of gen a buffer
* made by GM2000
*/
struct command_gen_buffer
{
	buffer& inBuffer;

	command_gen_buffer(buffer& inBuffer) :inBuffer(inBuffer) {}
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
		COMMAND_SET_BUFFER_DATA, COMMAND_GEN_BUFFER
	} commandType;

	//data
	void* data;

	gl_render_command(command_type commandType, void* data) :commandType(commandType), data(data) {}
};