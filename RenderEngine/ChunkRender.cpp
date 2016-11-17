
#include "ChunkRender.h"

chunk_render::chunk_render(unsigned char sight) :_sight(sight), render_node(chunkRenderShader)
{
	GLuint* block = new GLuint[1048576 * 2];

	for (unsigned j = 0; j < 1048576 * 2; j++)
	{
		block[j++] = 0;
		block[j] = (j + 1) / 2;
	}
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, 1048576 * 2 * sizeof(GLuint), block, _getShaderProgram());

	delete[]block;
}