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
struct canvas_shape
{
	const canvas_point_info points[3];

	//create shape with point data
	canvas_shape(const canvas_point_info& point1, const canvas_point_info& point2, const canvas_point_info& point3) :points{ point1,point2,point3 } {}
};

class canvas:public render_node
{
	gl_manager& glInstance = gl_manager::getInstance();

	//save all shape data
	std::vector<GLfloat> _renderData;

	//weather has change
	bool hasChange = false;

	//last vector size
	unsigned int lastVectorSize = 0;

	//draw canvas
	void _draw()
	{
		if (hasChange)
		{
			hasChange = false;

			_refreshShape();
		}

		if (_renderData.size() == 0)
			return;

		_shaderProgram->draw(0, _renderData.size() / 8);
	}

	//refresh shape
	void canvas::_refreshShape()
	{
		if (glInstance.bufferResize(_nodeBuffer, _renderData.capacity() * sizeof(GLfloat)))
			lastVectorSize = 0;

		_shaderProgram->setBufferData(&_renderData.at(0), lastVectorSize * sizeof(GLfloat), _renderData.size() * sizeof(GLfloat), _nodeBuffer);

		lastVectorSize = _renderData.size();
	}
	
public:
	canvas() :render_node() {}
	canvas(shader_program* shaderProgram) :render_node(shaderProgram) {}

	void addShape(const canvas_shape& shapeInfo);
	void clear();
};