#pragma once

#include "RenderEngine.h"

class application;

struct buffer
{
	GLuint vao = 0;
	GLuint vbo = 0;

	buffer() {}

	buffer(GLuint vaoID, GLuint vboID) :vao(vaoID), vbo(vboID) {}
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
	GLuint enableVAO = 0;
	GLuint enableVBO = 0;

protected:
	//start an window,only can be use in application::run()
	void _loadWindow();

	//save window
	GLFWwindow* _window;	
	
	//gl instance
	static gl_manager _glInstance;

	//init rendermanager
	gl_manager()
	{
		//init glfw
		glfwInit();
	}
public:
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
	//if return false it mean it is in use
	bool useBuffer(buffer bufferInfo)
	{
		if (bufferInfo.vao != enableVAO)
		{
			glBindVertexArray(bufferInfo.vao);
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			enableVAO = bufferInfo.vao;
			enableVBO = bufferInfo.vbo;

			return true;
		}
		else if (bufferInfo.vbo != enableVBO)
		{
			glBindBuffer(GL_ARRAY_BUFFER, bufferInfo.vbo);

			enableVBO = bufferInfo.vbo;
		}
		return false;
	}
	//get rendermanager instance
	static gl_manager& getInstance()
	{
		return _glInstance;
	}
};