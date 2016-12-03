
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
	if (!buffer.hasInit())
	{
		buffer.setInitFinish();

		glInstance.useShaderProgram(_programID);

		//block data
		glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, sizeof(GLuint) * 2 , (const void*)(sizeof(GLuint) * 0));
		glEnableVertexAttribArray(0);

		//nearby block info
		glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(GLuint) * 2, (const void*)(sizeof(GLuint) * 1));
		glEnableVertexAttribArray(1);
	}
}
