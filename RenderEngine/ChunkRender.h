#pragma once

#include "RenderNode.h"
#include "ChunkRenderShader.h"

class chunk_render :public render_node
{
private:
	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned char	_sight = 0;

	void _draw(camera _golbalCamera)
	{
		_glInstance.useBuffer(*_getBuffer());
		_glInstance.useTexture(*_getTexture());
		_glInstance.useShaderProgram(*_getShaderProgram());

		_getShaderProgram()->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

		//_glInstance.draw(0, 1048576);
		_glInstance.draw(0, 2500);
	}
public:
	chunk_render(unsigned char _sight);

	/*
	* set light pos
	* from the input location to 0,0,0
	*/
	void setLight(float x, float y, float z)
	{
		((chunk_render_shader*)_getShaderProgram())->setLight(x, y, z);
	}
	void setEyes(float x, float y, float z)
	{
		((chunk_render_shader*)_getShaderProgram())->setEyes(x, y, z);
	}
};