#pragma once

#include "RenderEngine.h"
#include "GLManager.h"
#include "RenderNode.h"
#include "Camera.h"

class color :public vec<GLfloat, 3>
{
public:
	color(float r, float g, float b) :vec<GLfloat, 3>({ r,g,b }) {}
};
class texture_pos :public vec<GLfloat, 2>
{
public:
	texture_pos(float x, float y) :vec<GLfloat, 2>({ x,y }) {}
};

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
private:
	gl_manager& _glInstance = gl_manager::getInstance();

	//save all shape data
	std::vector<GLfloat> _renderData;

	//weather has change
	bool _hasChange = false;

	//last vector size
	unsigned int _lastVectorSize = 0;

	//draw canvas
	void _draw(camera _golbalCamera)
	{
		_glInstance.useBuffer(_buffer);
		_glInstance.useShaderProgram(_shaderProgram);
		_glInstance.useTexture(_texture);

		if (_hasChange)
		{
			_hasChange = false;

			_refreshShape();
		}

		if (_renderData.size() == 0)
			return;

		_shaderProgram->setCamera(_golbalCamera + _nodeGolbalCamera,_modelCamera);

		_glInstance.draw(0, _renderData.size() / 8);
	}

	//refresh shape
	void canvas::_refreshShape()
	{
		if (_glInstance.bufferResize(_buffer, _renderData.capacity() * sizeof(GLfloat)))
			_lastVectorSize = 0;

		if (_renderData.size() != 0)
			_shaderProgram->setBufferData(&_renderData.at(0), _lastVectorSize * sizeof(GLfloat), _renderData.size() * sizeof(GLfloat), _buffer);

		_lastVectorSize = _renderData.size();
	}
	
public:
	canvas() :render_node() {}
	canvas(shader_program* shaderProgram) :render_node(shaderProgram) {}

	//add shape
	void addShape(const canvas_shape& shapeInfo);

	//clean all
	void clear();
};