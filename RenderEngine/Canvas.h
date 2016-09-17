#pragma once

#include "RenderEngine.h"
#include "GLManager.h"
#include "RenderNode.h"

class canvas:public render_node
{
	gl_manager& glInstance = gl_manager::getInstance();

public:
	canvas() :render_node()
	{
		//init attrib pointer
		glInstance.useBuffer(_nodeBuffer);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		GLfloat vertices[6][2] = 
		{
			{-0.90f, -0.90f },
			{ 0.85f, -0.90f },
			{-0.09f,  0.85f }
		};
		//test code
		glInstance.bufferData(_nodeBuffer, sizeof(vertices), vertices);
	}
	void draw()
	{
		glInstance.useBuffer(_nodeBuffer);
		glInstance.draw(0, 3);
	}
};