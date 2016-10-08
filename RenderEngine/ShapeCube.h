#pragma once

#include "Camera.h"
#include "Canvas.h"
#include "CanvasTexture.h"

class shape_cube
{
	canvas_shape _canvasShape[2];
public:
	shape_cube(cube_texture cubetexture, GLuint size, camera cubeDirection);

	operator canvas_shape*()
	{
		return _canvasShape;
	}
};