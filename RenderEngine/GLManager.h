#pragma once

#include "RenderEngine.h"
#include "Texture.h"
#include "Camera.h"

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
//please use new
class shader_program
{
	friend class gl_manager;

private:
	virtual void _draw(const GLint first, const GLsizei count) const = 0;
	virtual void _init() = 0;

protected:
	GLuint _projection = 0;
	GLuint _programID = 0;

public:
	virtual void setCamera(camera& globalCamera, camera& modelLocation) const;

	virtual void setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const = 0;
};
/*
rendermanager
it is used to do the basic thing
with opengl such as create an window
or create vao,vbo
*/
class gl_manager
{
	//sone function only can be use when the app start run
	friend class application;
	friend class shader_program;

private:
	//gl instance
	static gl_manager _glInstance;

	//save window size
	size_vec _windowSize{ 0,0 };

	//save the vao and vbo id that now use
	buffer _enableBuffer = buffer(-1, -1);

	//save the shader program list
	std::forward_list<shader_program*> _shaderProgramList;

	//save the texture list
	std::forward_list<texture> _textureList;

	//save the shader programid that is in use
	const void* _shaderProgram = nullptr;

	//the texture that now is in use
	texture _usingTexture;

	//start an window,only can be use in application::run()
	void _loadWindow(const size_vec &windowSize, const char* appName);

	//save window
	GLFWwindow* _window;

	//init rendermanager
	gl_manager()
	{
		//init glfw
		glfwInit();
	}
public:
	//add shader
	shader_program* genShader(char* vert, char* frag, shader_program* newShaderProgramClass);
	shader_program* genShader(char* vert, char* frag, char* gs, shader_program* newShaderProgramClass);

	//gen texture
	texture genTexture(const char* fileName[], GLuint count);

	//treate event
	void poolEvent() const
	{
		glfwPollEvents();
	}
	//swap buffer
	void swapBuffers() const
	{
		glfwSwapBuffers(_window);
	}
	//clear
	void clear(const GLbitfield& mask) const
	{
		glClear(mask);
	}
	//stop and clear
	void terminate() const
	{
		glfwTerminate();
	}
	//should close the window
	bool windowShouldClose() const
	{
		return glfwWindowShouldClose(_window) == 1;
	}
	//set buffer data
	void bufferData(buffer& buffer, const GLsizeiptr& size, const void* data)
	{
		useBuffer(buffer);

		buffer.size = size;

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	//set part of buffer data
	void bufferSubData(const buffer& buffer, const GLintptr offset, const GLsizeiptr size, const void* data)
	{
		useBuffer(buffer);

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
	//set buffer size
	bool bufferResize(buffer& buffer, const GLsizeiptr size)
	{
		if (buffer.size == size)
			return false;

		useBuffer(buffer);

		buffer.size = size;

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

		return true;
	}
	//genVAO
	GLuint genVAO() const
	{
		GLuint vao = 0;

		glGenVertexArrays(1, &vao);

		return vao;
	}
	//genVBO
	GLuint genVBO() const
	{
		GLuint vbo = 0;

		glGenBuffers(1, &vbo);

		return vbo;
	}
	//gen buffer
	buffer genBuffer() const
	{
		GLuint vao = 0;
		GLuint vbo = 0;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glGenBuffers(1, &vbo);

		//change back
		if (_enableBuffer.vao != -1)
		{
			glBindVertexArray(_enableBuffer.vao);
			glBindVertexArray(_enableBuffer.vbo);
		}

		return buffer(vao, vbo);
	}
	//draw buffer
	void draw(const GLint& first,const GLsizei& count)
	{
		((shader_program*)_shaderProgram)->_draw(first, count);
	}
	//if return false it mean it is in use
	bool useBuffer(const buffer& bufferInfo)
	{
		if (bufferInfo.vao != _enableBuffer.vao)
		{
			glBindVertexArray(bufferInfo.vao);
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			_enableBuffer.vao = bufferInfo.vao;
			_enableBuffer.vbo = bufferInfo.vbo;

			return true;
		}
		else if (bufferInfo.vbo != _enableBuffer.vbo)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			_enableBuffer.vbo = bufferInfo.vbo;
		}
		return false;
	}
	//use program
	void useShaderProgram(const shader_program* shaderProgram)
	{
		if (_shaderProgram == nullptr || ((shader_program*)_shaderProgram)->_programID != shaderProgram->_programID)
		{
			_shaderProgram = shaderProgram;

			glUseProgram(shaderProgram->_programID);
		}
	}
	//use texture
	void useTexture(const texture& texture)
	{
		if (_usingTexture == texture)
			return;

		_usingTexture = texture;

		//no texture
		if (texture._textureCount == 0)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		else
			//has texture
			for (unsigned int i = 0; i < texture._textureCount; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texture._textureIDList[i]);
			}
	}
	//get rendermanager instance
	static gl_manager& getInstance()
	{
		return _glInstance;
	}

	//free program list
	~gl_manager()
	{
		for (auto* shaderProgram : _shaderProgramList)
		{
			delete(shaderProgram);
		}
		for (auto texture : _textureList)
		{
			texture.deleteTexture();
		}
	}
};