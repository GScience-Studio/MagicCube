
#include "ShapeCube.h"

shape_cube::shape_cube(cube_texture cubetexture, GLuint size) :_canvasShape
{
	canvas_shape
	(
		canvas_point_info(color(cubetexture.textureColor[0].get(0), cubetexture.textureColor[0].get(1), cubetexture.textureColor[0].get(2)), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(cubetexture.texturePos[3].get(0), cubetexture.texturePos[3].get(1))),
		canvas_point_info(color(cubetexture.textureColor[1].get(0), cubetexture.textureColor[1].get(1), cubetexture.textureColor[1].get(2)), location<GLfloat>(-1.0f, 1.0f, 0.0f), texture_pos(cubetexture.texturePos[0].get(0), cubetexture.texturePos[0].get(1))),
		canvas_point_info(color(cubetexture.textureColor[2].get(0), cubetexture.textureColor[2].get(1), cubetexture.textureColor[2].get(2)), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(cubetexture.texturePos[1].get(0), cubetexture.texturePos[1].get(1)))
	)
	,
	canvas_shape
	(
		canvas_point_info(color(cubetexture.textureColor[0].get(0), cubetexture.textureColor[0].get(1), cubetexture.textureColor[0].get(2)), location<GLfloat>(-1.0f, -1.0f, 0.0f), texture_pos(cubetexture.texturePos[1].get(0), cubetexture.texturePos[1].get(1))),
		canvas_point_info(color(cubetexture.textureColor[1].get(0), cubetexture.textureColor[1].get(1), cubetexture.textureColor[1].get(2)), location<GLfloat>(1.0f, -1.0f, 0.0f), texture_pos(cubetexture.texturePos[2].get(0), cubetexture.texturePos[2].get(1))),
		canvas_point_info(color(cubetexture.textureColor[2].get(0), cubetexture.textureColor[2].get(1), cubetexture.textureColor[2].get(2)), location<GLfloat>(1.0f, 1.0f, 0.0f), texture_pos(cubetexture.texturePos[3].get(0), cubetexture.texturePos[3].get(1)))
	)
}
{}