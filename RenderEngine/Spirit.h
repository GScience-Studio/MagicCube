#pragma once

#include "RenderEngine.h"

struct spirit
{
	//vao id
	GLuint _vaoId;

	//address in vbo
	void* _address;

	spirit(GLuint vaoId, void* address) :_vaoId(vaoId), _address(address) {}
};