#pragma once

#include "RenderEngine.h"

class buffer
{
	friend class gl_manager;
	friend class shader_program;

private:
	//save buffer ID
	GLuint _vao = 0;
	GLuint _vbo = 0;

	//buffer size
	GLsizeiptr	_size = 0;

	//has init
	bool	_hasInit = false;

	buffer(GLuint vao, GLuint vbo) :_vao(vao), _vbo(vbo) {}

	//is equal
	bool operator ==(buffer buffer)
	{
		return _vao == buffer._vao && _vbo == buffer._vbo;
	}

public:
	const GLuint getVAO()
	{
		return _vao;
	}
	const GLuint getVBO()
	{
		return _vao;
	}
	const GLsizeiptr getSize()
	{
		return _size;
	}
	bool hasInit()
	{
		return _hasInit;
	}
	void setInitFinish()
	{
		_hasInit = true;
	}

	//null buffer
	buffer() {}
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