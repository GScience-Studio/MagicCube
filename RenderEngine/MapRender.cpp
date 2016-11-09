
#include "MapRender.h"

map_render::map_render(unsigned char sight) :_sight(sight), render_node(mapRenderShader)
{
	int block[200000]{ 0 };

	for (unsigned j = 0; j < 100000; j++)
	{
		block[j * 2] = j;
	}
	_shaderProgram->setBufferData(&block, 0, 200000, _buffer);
}