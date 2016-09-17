#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

class render_node
{
protected:
	buffer _nodeBuffer;
	
	gl_manager& _glInstance = gl_manager::getInstance();

	bool _isEnable = false;

public:
	//each node must can be draw
	virtual void draw()
	{
		if (_isEnable)
			_glInstance.useBuffer(_nodeBuffer);
	}
	//init
	render_node(buffer buffer) :_nodeBuffer(buffer) {}

	render_node()
	{
		_nodeBuffer = _glInstance.genBuffer();
	}
};