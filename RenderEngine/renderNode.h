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
	render_program* _renderProgram;
	buffer*			_buffer = new buffer();
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
		}
	}

	render_node(render_program* renderProgram)
	{
		_renderProgram = renderProgram;
	}
	render_node(buffer* buffer, render_program* renderProgram) :_buffer(buffer)
	{
		_renderProgram = renderProgram;
	}

	buffer* _getBuffer()
	{
		return _buffer;
	}

	render_program* _getRenderProgram()
	{
		return _renderProgram;
	}

	const texture* _getTexture()
	{
		return _texture;
	}
	~render_node()
	{
		delete(_buffer);
	}
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
	camera* getModelCamera()
	{
		return &_modelLocation;
	}
};