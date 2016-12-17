#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
	friend class scene_node;
	friend class render_node_manager;

private:
	bool operator < (const render_node& renderNode) const
	{
		return _priority < renderNode._priority;
	}
	bool operator <= (const render_node& renderNode) const
	{
		return _priority <= renderNode._priority;
	}
	bool operator > (const render_node& renderNode) const
	{
		return _priority > renderNode._priority;
	}
	bool operator >= (const render_node& renderNode) const
	{
		return _priority >= renderNode._priority;
	}
	bool operator == (const render_node& renderNode) const
	{
		return renderNode._priority == _priority;
	}

	gl_manager&		_glInstance = gl_manager::getInstance();

	//these are the thing that about opengl
	render_program* _renderProgram;
	buffer*			_buffer;

	const texture*	_texture;

	bool _isBufferOwner = false;

protected:
	//node camera
	camera_synchronize		_nodeCamera;
	camera_synchronize		_modelLocation;
	
	//node priority(0.0 to 1.0),0.0 is lowest and 1.0 is highest
	float _priority = 0.0;

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
		_isBufferOwner = true;
		_buffer = new buffer();
		_renderProgram = renderProgram;
	}
	render_node(buffer* buffer, render_program* renderProgram) :_buffer(buffer)
	{
		_isBufferOwner = false;
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
		if (_isBufferOwner)
		{
			delete(_buffer);
		}
	}
public:
	//texture
	void bindTexture(const texture* texture)
	{
		_texture = texture;
	}
	//golbal Camera
	camera_synchronize* getNodeCamera()
	{
		return &_nodeCamera;
	}
	//model camera
	camera_synchronize* getModelCamera()
	{
		return &_modelLocation;
	}
};