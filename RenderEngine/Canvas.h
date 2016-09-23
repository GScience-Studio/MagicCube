#pragma once

#include <vector>

#include "RenderEngine.h"
#include "GLManager.h"
#include "RenderNode.h"

typedef vec<GLfloat, 3>		color;
typedef vec<GLfloat, 2>		texture_pos;

//shape info
struct canvas_point_info
{
	//location
	const location<GLfloat>	locationData;

	//color
	const color				colorData;

	//texture pos
	const texture_pos		texturePosData;

	canvas_point_info(const color& color, const location<GLfloat>& location, const texture_pos& texturePos) :colorData(color), locationData(location), texturePosData(texturePos) {}
};
struct canvas_shape_info
{
	const canvas_point_info points[3];

	canvas_shape_info(const canvas_point_info& point1, const canvas_point_info& point2, const canvas_point_info& point3) :points{ point1,point2,point3 } {}
};

class canvas_shape
{
	buffer		_canvasBuffer;
	void*		_shapeLocation;

public:
	canvas_shape(const buffer& buffer, void* location) :_canvasBuffer(buffer), _shapeLocation(location) {}
};

class canvas:public render_node
{
	gl_manager& glInstance = gl_manager::getInstance();

	//save all shape data
	std::vector<GLfloat> _renderData;

	//weather has change
	bool hasChange = false;

	//draw canvas
	void _draw()
	{
		if (hasChange)
		{
			hasChange = false;

			_shaderProgram->createBuffer(&_renderData.at(0), _renderData.size() * sizeof(GLfloat), _nodeBuffer);
		}

		if (_renderData.size() == 0)
			return;

		_shaderProgram->draw(0, _renderData.size() / 8);
	}

	//refresh shape
	const void canvas::_refreshShape(GLfloat* shapeData, GLsizeiptr size);
	
public:
	canvas() :render_node() {}
	canvas(shader_program* shaderProgram) :render_node(shaderProgram) {}

	const canvas_shape addShape(const canvas_shape_info& shapeInfo);
};