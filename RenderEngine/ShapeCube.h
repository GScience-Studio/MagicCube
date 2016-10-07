#pragma once

#include "Canvas.h"
#include "CanvasTexture.h"

enum cube_direction
{
	FRONT, BACK, LEFT, RIGHT, UP, DOWN
};
class shape_cube :public canvas_shape
{
public:
	shape_cube(cube_direction cubeDirection, canvas_texture texture);
};