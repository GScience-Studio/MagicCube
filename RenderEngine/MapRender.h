#pragma once

#include "RenderNode.h"
#include "MapRenderShader.h"

class map_render :public render_node
{
private:
	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned char	_sight = 0;
public:
	map_render(unsigned char _sight);

	void _draw(camera _golbalCamera)
	{
		_glInstance.useBuffer(_buffer);
		_glInstance.useTexture(_texture);
		_glInstance.useShaderProgram(_shaderProgram);

		_shaderProgram->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

		_glInstance.draw(0, 1048576);
		//_glInstance.draw(0, 1);
	}
};