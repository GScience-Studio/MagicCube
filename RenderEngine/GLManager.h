#pragma once

#include "RenderEngine.h"

#include <forward_list>

class application;

struct buffer
{
	GLuint vao = 0;
	GLuint vbo = 0;

	buffer() {}

	buffer(GLuint vaoID, GLuint vboID) :vao(vaoID), vbo(vboID) {}

	bool operator ==(buffer buffer)
	{
		return vao == buffer.vao && vbo == buffer.vbo;
	}
};
//please use new
class shader_program
{
	friend class gl_manager;

protected:

	//only can use new
	~shader_program() {}
	shader_program() {}
public:
	GLuint programID = 0;

	virtual void createBuffer(void* bufferData, const GLsizeiptr size, const buffer& buffer) const = 0;
	virtual void draw(GLint start, GLsizei end) = 0;
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

	//save the vao and vbo id that now use
	buffer enableBuffer = buffer(-1, -1);

	//save the shader program list
	std::forward_list<shader_program*> _shaderProgramList;

	//save the shader programid that is in use
	GLuint shaderProgramID = 0;

	//basic shader program
	class normail3DShader :public shader_program
	{
	private:
		gl_manager& glInstance = gl_manager::getInstance();

	public:
		void createBuffer(void* bufferData, const GLsizeiptr size, const buffer& buffer) const
		{
			glInstance.useBuffer(buffer);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
			
			glInstance.bufferData(buffer, size, bufferData);
		}

		void draw(GLint start, GLsizei end)
		{
			glInstance.useShaderProgram(this);
			glInstance.draw(start, end);
		}
	};
private:
	//start an window,only can be use in application::run()
	void _loadWindow();

	//save window
	GLFWwindow* _window;	
	
	//gl instance
	static gl_manager _glInstance;

	//init rendermanager
	gl_manager()
	{
		//init shader pointer
		appNormail3DShader = new normail3DShader();

		//init glfw
		glfwInit();
	}
public:
	//save shader pointer
	normail3DShader* appNormail3DShader;

	//add shader
	shader_program* addShader(char* vert, char* frag, shader_program* newShaderProgramClass);

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
	void clear(GLbitfield mask) const
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
	void bufferData(buffer buffer, GLsizeiptr size, void* data)
	{
		useBuffer(buffer);

		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	//set part of buffer data
	void bufferSubData(buffer buffer, GLintptr offset, GLsizeiptr size, void* data)
	{
		useBuffer(buffer);

		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
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
		if (enableBuffer.vao != -1)
		{
			glBindVertexArray(enableBuffer.vao);
			glBindVertexArray(enableBuffer.vbo);
		}

		return buffer(vao, vbo);
	}
	//draw buffer
	void draw(GLint fitst,GLsizei count)
	{
		glDrawArrays(GL_TRIANGLES, fitst, count);
	}
	//if return false it mean it is in use
	bool useBuffer(buffer bufferInfo)
	{
		if (bufferInfo.vao != enableBuffer.vao)
		{
			glBindVertexArray(bufferInfo.vao);
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			enableBuffer.vao = bufferInfo.vao;
			enableBuffer.vbo = bufferInfo.vbo;

			return true;
		}
		else if (bufferInfo.vbo != enableBuffer.vbo)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			enableBuffer.vbo = bufferInfo.vbo;
		}
		return false;
	}
	//use program
	void useShaderProgram(shader_program* shaderProgram)
	{
		if (shaderProgramID != shaderProgram->programID)
		{
			shaderProgramID = shaderProgram->programID;

			glUseProgram(shaderProgram->programID);
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
	}
};