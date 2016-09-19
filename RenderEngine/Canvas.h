#pragma once

#include "RenderEngine.h"
#include "GLManager.h"
#include "RenderNode.h"

class canvas:public render_node
{
	gl_manager& glInstance = gl_manager::getInstance();

	GLfloat testNumber = -0.90f;

public:
	canvas() :render_node()
	{
		GLfloat vertices[6][2] = 
		{
			{-0.90f, -0.90f },
			{ 0.85f, -0.90f },
			{-0.09f,  0.85f }
		};

		_shaderProgram->createBuffer(vertices, sizeof(vertices), _nodeBuffer);
	}
	void draw()
	{
		testNumber = -testNumber;

		GLfloat vertices[6][2] =
		{
			{ -0.90f, testNumber },
			{ 0.85f, -0.90f },
			{ -0.09f,  0.85f }
		};

		_shaderProgram->createBuffer(vertices, sizeof(vertices), _nodeBuffer);

		_shaderProgram->draw(0, 3);
	}
};