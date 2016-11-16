#pragma once

#include "RenderEngine.h"

class texture
{
	friend class gl_manager;

private:
	//save the info of texture
	GLuint  _textureCount = 0;
	GLuint* _textureIDList = nullptr;

	//create an new texture
	void createTexture(GLuint count, GLuint* idList)
	{
		_textureCount = count;

		_textureIDList = idList;
	}

	//delete texture
	void _deleteTexture()
	{
		delete[](_textureIDList);
	}
	bool operator ==(const texture& texture)
	{
		return _textureIDList == texture._textureIDList;
	}

	//don't all user create texture
	texture() {}
};