#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
protected:
	gl_manager& _glInstance = gl_manager::getInstance();

	shader_program* _shaderProgram;
	buffer			_nodeBuffer;

	bool _isEnable = false;

public:
	//each node must can be draw
	virtual void draw()
	{
		if (_isEnable)
			_glInstance.useBuffer(_nodeBuffer);
	}
	//init
	render_node(buffer buffer) :_nodeBuffer(buffer)
	{
		_shaderProgram = gl_manager::getInstance().appNormail3DShader;
	}

	render_node()
	{
		_nodeBuffer		= _glInstance.genBuffer();
		_shaderProgram	= gl_manager::getInstance().appNormail3DShader;
	}
};