#pragma once

#include "RenderEngine.h"
#include "Texture.h"

class texture_node
{
private:
	texture _texture;

public:
	texture_node(const texture texture) :_texture(texture) {}
	texture_node() {}

	void bindTexture(const texture& texture)
	{
		_texture = texture;
	}
};