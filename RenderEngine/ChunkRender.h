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
		_glInstance.useBuffer(_buffer);
		_glInstance.useTexture(_texture);
		_glInstance.useShaderProgram(_shaderProgram);

		_shaderProgram->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

		_glInstance.draw(0, 1048576);
		//_glInstance.draw(0, 1000);
	}
public:
	chunk_render(unsigned char _sight);

	/*set light pos
	from the input location to 0,0,0
	*/
	void setLight(float x, float y, float z)
	{
		((chunk_render_shader*)_shaderProgram)->setLight(x, y, z);
	}
	void setEyes(float x, float y, float z)
	{
		((chunk_render_shader*)_shaderProgram)->setEyes(x, y, z);
	}
};