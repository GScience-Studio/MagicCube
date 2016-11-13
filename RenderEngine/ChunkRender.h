#pragma once

#include "RenderNode.h"
#include "ChunkRenderShader.h"

class chunk_render :public render_node
{
private:
	gl_manager& _glInstance = gl_manager::getInstance();

	unsigned char	_sight = 0;

	bool hasInit = false;

	void _draw(camera _golbalCamera)
	{
		_glInstance.useBuffer(*_getBuffer());
		_glInstance.useTexture(*_getTexture());
		_glInstance.useShaderProgram(*_getShaderProgram());

		_getShaderProgram()->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

		//_glInstance.draw(0, 1048576);
		_glInstance.draw(0, 2500);
	}
	void _refreshData()
	{
		if (!hasInit)
		{
			hasInit = true;

			GLuint* block = new GLuint[1048576 * 2];

			for (unsigned j = 0; j < 1048576 * 2; j++)
			{
				block[j++] = 0;
				block[j] = (j + 1) / 2;
			}
			_getShaderProgram()->setBufferData(block, 0, 1048576 * 2 * sizeof(GLuint), *_getBuffer());

			delete[]block;
		}
	}
public:
	chunk_render(unsigned char _sight);

	/*set light pos
	from the input location to 0,0,0
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