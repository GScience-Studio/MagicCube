
#include "MapRender.h"

map_render::map_render(unsigned char sight) :_sight(sight), render_node(mapRenderShader)
{
	int* block = new int[1048576 * 2];

	for (unsigned j = 0; j < 1048576 * 2; j++)
	{
		block[j++] = 0;
		block[j] = (j + 1) / 2;
	}
	_shaderProgram->setBufferData(block, 0, 1048576 * 2 * sizeof(GLuint), _buffer);

	delete[]block;
}