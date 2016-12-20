
#include "ChunkRenderShader.h"

render_program* chunkRenderProgram;

void chunk_render_program::_setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const
{
	glInstance.useBuffer(buffer);

	if (buffer.getSize() >= size)
	{
		glInstance.bufferSubData(buffer, differentBufferDataPos, size, bufferData);
	}
	else
	{
		glInstance.bufferData(buffer, size, bufferData);
	}
}
