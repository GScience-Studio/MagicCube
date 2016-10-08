#pragma once

#include "RenderEngine.h"

struct cube_texture
{
	vec<texture_pos, 4> texturePos;
	vec<color, 4>		textureColor;

	//set texture pos
	cube_texture(vec<texture_pos, 4> texturePos, vec<color, 4> textureColor) :texturePos(texturePos), textureColor(textureColor) {}
};
class tileset_texture :public cube_texture
{
public:
	tileset_texture(cube_texture canvasTexture) :cube_texture(canvasTexture) {}
};