#pragma once

#include "RenderEngine.h"
#include "InputCallback.h"
#include "Texture.h"
#include "Camera.h"
#include "GLRenderCommands.h"

//queue
#include <queue>

//glm
#include <glm\gtc\type_ptr.hpp>

class buffer
{
	friend class gl_manager;
	friend class render_program;

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
class render_program
{
	friend class gl_manager;

protected:
	void _setCamera(camera& globalCamera, camera& modelLocation);

	virtual void _init() = 0;

	virtual void _setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const = 0;

	GLuint _projection = 0;
	GLuint _programID = 0;

public:
	virtual void drawBuffer(const GLint first, const GLsizei count, buffer& buffer, camera& globalCamera, camera& modelLocation) = 0;
};

/*
* rendermanager
* it is used to do the basic thing
with opengl such as create an window
or create vao,vbo
*/
class gl_manager: public input_callback
{
	//sone function only can be use when the app start run
	friend class application;
	friend class render_program;

private:
	//gl instance
	static gl_manager _glInstance;

	//queue list
	std::queue<gl_render_command> _renderQueue;
	
	//render queue lock
	std::mutex _renderQueueLock;

	//save the vao and vbo id that now use
	buffer _enableBuffer = buffer(-1, -1);

	//save the shader program list
	std::forward_list<render_program*> _renderProgramList;

	//save the texture list
	std::forward_list<texture*> _textureList;

	//save the shader programid that is in use
	GLuint _shaderProgramID = 0;

	//the texture that now is in use
	const texture* _usingTexture;

	//start an window,only can be use in application::run()
	void _loadWindow(const size_vec &windowSize, const char* appName);

	//save window
	GLFWwindow* _window;

	//projection
	glm::mat4 _perspective;

	//windows size change event
	void windowsSizeChangeListener(int width, int height);

	//main thread ID
	std::thread::id threadID = std::this_thread::get_id();

	//init rendermanager
	gl_manager()
	{
		//init glfw
		glfwInit();
	}

	/*
	* refresh render command queue
	* made by GM2000
	*/
	void _refreshQueue();

public:
	//add shader
	render_program* bindShader(char* vert, char* frag, render_program* newShaderProgramClass);
	render_program* bindShader(char* vert, char* frag, char* gs, render_program* newShaderProgramClass);

	//gen texture
	texture* genTexture(const char* fileName[], GLuint count);

	//treate event
	void pollEvent() const
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
	bool windowShouldClose()
	{
		return glfwWindowShouldClose(_window) == 1;
	}
	//use shader
	void useShaderProgram(const GLuint programID)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return;
		}
#endif
		if (_shaderProgramID == programID)
			return;

		_shaderProgramID = programID;

		glUseProgram(_shaderProgramID);
	}
	/*
	* set buffer data
	* thread-safety: can be call in all thread
	* made by GM2000
	*/
	void bufferData(buffer& inBuffer, const unsigned int differentBufferDataPos, const GLsizeiptr& size, const void* data, render_program* renderProgram)
	{
		if (std::this_thread::get_id() != threadID)
		{
			//copy data
			void* dataCopy = malloc(size);

			memcpy(dataCopy, data, size);

			//create queue and add to renderqueue
			command_set_buffer_data* renderCommand = new command_set_buffer_data(&inBuffer, differentBufferDataPos, size, dataCopy, renderProgram);

			_renderQueueLock.lock();

			_renderQueue.push(gl_render_command(gl_render_command::COMMAND_SET_BUFFER_DATA, (void*)renderCommand));

			_renderQueueLock.unlock();

			return;
		}

		renderProgram->_setBufferData(data, differentBufferDataPos, size, inBuffer);
	}

	/*
	* set the buffer by shader
	* thread-safety: will only call in main thread
	* made by GM2000
	*/
	void bufferData(buffer& inBuffer, const GLsizeiptr& size, const void* data)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return;
		}
#endif

		useBuffer(inBuffer);

		inBuffer._size = size;

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	/*
	* set part of buffer data
	* thread-safety: only can be call in the main thread
	* made by GM2000
	*/
	void bufferSubData(buffer& inBuffer, const GLintptr offset, const GLsizeiptr size, const void* data)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return;
		}
#endif

		useBuffer(inBuffer);

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}
	/*
	* set buffer size
	* thread-safety: only can be call in main thread
	* made by GM2000
	*/
	bool bufferResize(buffer& buffer, const GLsizeiptr size)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return false;
		}
#endif

		if (buffer._size == size)
			return false;

		useBuffer(buffer);

		buffer._size = size;

		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);

		return true;
	}
	//genVAO
	GLuint genVAO() const
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return -1;
		}
#endif

		GLuint vao = 0;

		glGenVertexArrays(1, &vao);

		return vao;
	}
	//genVBO
	GLuint genVBO() const
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return -1;
		}
#endif

		GLuint vbo = 0;

		glGenBuffers(1, &vbo);

		return vbo;
	}
	//gen buffer
	void genBuffer(buffer* inBuffer)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return;
		}
#endif

		glGenVertexArrays(1, &inBuffer->_vao);
		glBindVertexArray(inBuffer->_vao);
		glGenBuffers(1, &inBuffer->_vbo);

		//change back
		if (_enableBuffer._vao != -1)
		{
			glBindVertexArray(_enableBuffer._vao);
			glBindVertexArray(_enableBuffer._vbo);
		}
	}
	//if return false it mean it is in use
	bool useBuffer(buffer& bufferInfo)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return false;
		}
#endif

		if (bufferInfo.getVAO() == 0)
			genBuffer(&bufferInfo);

		if (bufferInfo._vao != _enableBuffer._vao)
		{
			glBindVertexArray(bufferInfo._vao);
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo._vbo);

			_enableBuffer._vao = bufferInfo._vao;
			_enableBuffer._vbo = bufferInfo._vbo;

			return true;
		}
		else if (bufferInfo._vbo != _enableBuffer._vbo)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo._vbo);

			_enableBuffer._vbo = bufferInfo._vbo;
		}
		return false;
	}
	//use texture
	void useTexture(const texture& texture)
	{
#ifdef _DEBUG
		if (std::this_thread::get_id() != threadID)
		{
			message("[Warning]void useShader(const GLuint programID) can only use in main thread!", msgWarning, false);

			return;
		}
#endif

		if (_usingTexture == &texture)
			return;

		if (&texture == nullptr)
			return;

		//no texture
		if (texture._textureCount != 0)
			//has texture
			for (unsigned int i = 0; i < texture._textureCount; i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texture._textureIDList[i]);
			}

		//has load texture before?
		if (_usingTexture != nullptr)
			//need disable texture?
			if (_usingTexture->_textureCount > texture._textureCount)
				//disable some texture
				for (unsigned int i = texture._textureCount; i < _usingTexture->_textureCount; i++)
				{
					glActiveTexture(GL_TEXTURE0 + i);

					glBindTexture(GL_TEXTURE_2D, 0);
				}

		//set new texture
		_usingTexture = &texture;
	}
	//get rendermanager instance
	static gl_manager& getInstance()
	{
		return _glInstance;
	}

	//free program list
	~gl_manager()
	{
		for (auto* shaderProgram : _renderProgramList)
		{
			delete(shaderProgram);
		}
		for (auto texture : _textureList)
		{
			texture->_deleteTexture();

			delete(texture);
		}
	}
};