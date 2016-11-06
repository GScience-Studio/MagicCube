
#include "MapRender.h"

map_render::map_render(unsigned char sight) :_sight(sight), render_node(mapRenderShader)
{
	int i[]{ 0,0,0 };

	_shaderProgram->setBufferData(&i, 0, 1, _buffer);
}