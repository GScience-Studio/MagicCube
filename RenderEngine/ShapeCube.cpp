
#include "ShapeCube.h"

shape_cube::shape_cube(cube_direction cubeDirection, canvas_texture texture) :canvas_shape
(
	canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(0.0f, 1.0f)),
	canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(1.0f, -1.0f, 0.0f), texture_pos(1.0f, 1.0f)),
	canvas_point_info(color(0.0f, 0.0f, 0.0f), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(1.0f, 0.0f))
) {}