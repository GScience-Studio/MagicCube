#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
	friend class scene_node;
	friend class render_node_manager;

private:
	gl_manager&		_glInstance = gl_manager::getInstance();

protected:
	//these are the thing that about opengl
	shader_program* _shaderProgram;
	buffer			_buffer;
	texture			_texture;

	//node camera
	camera			_nodeCamera;
	camera			_modelLocation;

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
	render_node(shader_program* shaderProgram)
	{
		_buffer = _glInstance.genBuffer();
		_shaderProgram = shaderProgram;
	}
	render_node(buffer buffer, shader_program* shaderProgram) :_buffer(buffer)
	{
		_shaderProgram = shaderProgram;
	}

	~render_node() {}
public:
	//texture
	void bindTexture(const texture& texture)
	{
		_texture = texture;
	}
	//golbal Camera
	camera* getNodeCamera()
	{
		return &_nodeCamera;
	}
	//model camera
	camera* getModelLocation()
	{
		return &_modelLocation;
	}
};