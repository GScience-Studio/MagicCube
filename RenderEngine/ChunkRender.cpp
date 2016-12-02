
#include "ChunkRender.h"

#define HIDE_TOP		0x01
#define HIDE_DOWM		0x02
#define HIDE_LEFT		0x04
#define HIDE_RIGHT		0x08
#define HIDE_BACK		0x10
#define HIDE_TOWARD		0x20

chunk_render::chunk_render(unsigned char sight) :_sight(sight), render_node(chunkRenderProgram)
{
	GLuint* block = new GLuint[256 * 3];

	std::cout << sizeof(uint32_t) << std::endl;

	for (unsigned j = 0; j < 256 * 3; j++)
	{
		block[j++] = 0;
		block[j++] = (j + 1) / 3;
		block[j] = 0xFFFFFF00 | HIDE_LEFT | HIDE_RIGHT | HIDE_BACK | HIDE_TOWARD;
	}
	gl_manager::getInstance().bufferData(*_getBuffer(), 0, 256 * 3 * sizeof(GLuint), block, _getRenderProgram());

	delete[]block;
}