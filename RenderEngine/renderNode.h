#pragma once

#include "RenderEngine.h"
#include "GLManager.h"
#include "NormalShader.h"

class render_node
{
	friend class scene;

private:
	gl_manager&		_glInstance = gl_manager::getInstance();

protected:
	//these are the thing that about opengl
	shader_program* _shaderProgram;
	buffer			_buffer;
	texture			_texture;

	//node camera
	camera			_nodeGolbalCamera;
	camera			_modelCamera;

	//is the render_node can draw
	bool _isEnable = false;

	//each node must can be draw
	virtual void _draw(camera _golbalCamera)
	{
		if (_isEnable)
		{
			_glInstance.useBuffer(_buffer);
			_glInstance.useTexture(_texture);
			_glInstance.useShaderProgram(_shaderProgram);
		}
	}

public:
	//init
	render_node(buffer buffer) :_buffer(buffer)
	{
		_shaderProgram = normal3DShader;
	}
	render_node(shader_program* shaderProgram)
	{
		_buffer			= _glInstance.genBuffer();
		_shaderProgram	= shaderProgram;
	}
	render_node(buffer buffer, shader_program* shaderProgram) :_buffer(buffer)
	{
		_shaderProgram = shaderProgram;
	}

	render_node()
	{
		_buffer			= _glInstance.genBuffer();
		_shaderProgram	= normal3DShader;
	}
	//texture
	void bindTexture(const texture& texture)
	{
		_texture = texture;
	}
	//golbal Camera
	camera* getGolbalCamera()
	{
		return &_nodeGolbalCamera;
	}
	//model camera
	camera* getModelCamera()
	{
		return &_modelCamera;
	}
};