
#include "ChunkRender.h"

chunk_render::chunk_render(unsigned char sight) :_sight(sight), render_node(chunkRenderProgram)
{
	GLuint* block = new GLuint[100 * 2];

	for (unsigned j = 0; j < 100 * 2; j++)
	{
		block[j++] = 0;
		block[j] = (j + 1) / 2;
	}
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, 100 * 2 * sizeof(GLuint), block, _getRenderProgram());

	delete[]block;
}