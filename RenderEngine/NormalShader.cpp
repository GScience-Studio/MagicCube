
#include "NormalShader.h"

shader_program* normal2DShader;
shader_program* normal3DShader;

void normal_3d_shader::_setBufferData(const void* bufferData, const unsigned int differentBufferDataPos, const GLsizeiptr size, buffer& buffer) const
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

		//location data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		//color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		//texture pos
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
}
