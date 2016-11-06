
#include "MapRenderShader.h"

shader_program* mapRenderShader;

void map_render_shader::setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const
{
	glInstance.useBuffer(buffer);

	if (buffer.size >= size)
	{
		glInstance.bufferSubData(buffer, differentBufferDataPos, size, bufferData);
	}
	else
	{
		glInstance.bufferData(buffer, size, bufferData);
	}
	if (!buffer.hasInit)
	{
		buffer.hasInit = true;

		//block data
		glVertexAttribPointer(0, 1, GL_UNSIGNED_INT, GL_FALSE, 1 * sizeof(GLuint), 0);
		glEnableVertexAttribArray(0);
	}
}
