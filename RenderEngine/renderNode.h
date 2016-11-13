#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
	friend class scene_node;
	friend class render_node_manager;

private:
	gl_manager&		_glInstance = gl_manager::getInstance();

	//these are the thing that about opengl
	shader_program* _shaderProgram;
	buffer			_buffer;
	const texture*	_texture;

protected:
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
			_glInstance.useBuffer(*_getBuffer());
			_glInstance.useTexture(*_getTexture());
			_glInstance.useShaderProgram(*_getShaderProgram());
		}
	}
	//automatic refresh data
	virtual void _refreshData()
	{

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

	buffer* _getBuffer()
	{
		if (_buffer.vao == 0 || _buffer.vbo == 0)
			_buffer = _glInstance.genBuffer();

		return &_buffer;
	}

	shader_program* _getShaderProgram()
	{
		return _shaderProgram;
	}

	const texture* _getTexture()
	{
		return _texture;
	}
	~render_node() {}
public:
	//texture
	void bindTexture(const texture* texture)
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