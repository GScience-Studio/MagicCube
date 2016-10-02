#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
	friend class scene;

private:
	gl_manager& _glInstance = gl_manager::getInstance();

protected:
	//these are the thing that about opengl
	shader_program* _shaderProgram;
	buffer			_nodeBuffer;

	//is the render_node can draw
	bool _isEnable = false;

	//each node must can be draw
	virtual void _draw()
	{
		if (_isEnable)
			_glInstance.useBuffer(_nodeBuffer);
	}

public:
	//init
	render_node(buffer buffer) :_nodeBuffer(buffer)
	{
		_shaderProgram = gl_manager::getInstance().appNormail3DShader;
	}
	render_node(shader_program* shaderProgram)
	{
		_nodeBuffer		= _glInstance.genBuffer();
		_shaderProgram	= shaderProgram;
	}
	render_node(buffer buffer, shader_program* shaderProgram) :_nodeBuffer(buffer)
	{
		_shaderProgram = shaderProgram;
	}

	render_node()
	{
		_nodeBuffer		= _glInstance.genBuffer();
		_shaderProgram	= gl_manager::getInstance().appNormail3DShader;
	}
};