#pragma once

#include "GLManager.h"
#include "RenderNode.h"
#include "Camera.h"

class color :public vec<GLfloat, 3>
{
public:
	color(float r, float g, float b) :vec<GLfloat, 3>({ r,g,b }) {}
	color() :vec<GLfloat, 3>({ 0.0f,0.0f,0.0f }) {}
};
class texture_pos :public vec<GLfloat, 2>
{
public:
	texture_pos(float x, float y) :vec<GLfloat, 2>({ x,y }) {}
	texture_pos() :vec<GLfloat, 2>({ 0,0 }) {}
};

//shape info
struct canvas_point_info
{
	//location
	location<GLfloat>	locationData;

	//color
	color				colorData;

	//texture pos
	texture_pos			texturePosData;

	canvas_point_info(const color& color, const location<GLfloat>& location, const texture_pos& texturePos) :colorData(color), locationData(location), texturePosData(texturePos) {}
};
struct canvas_shape
{
	canvas_point_info points[3];

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
	void _draw(camera _golbalCamera);

	//refresh shape
	void _refreshShape();
	
public:
	canvas(shader_program* shaderProgram) :render_node(shaderProgram) {}

	//add shape
	void addShapes(canvas_shape* shapeInfo, unsigned int count);
	void addShapes(const void* data, unsigned int count);

	//clean all
	void clear();
};