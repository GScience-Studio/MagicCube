
#include "Canvas.h"

const void canvas::_refreshShape(GLfloat* shapeData,GLsizeiptr size)
{
	_shaderProgram->createBuffer(shapeData, size, _nodeBuffer);
}

const canvas_shape canvas::addShape(const canvas_shape_info& shapeInfo)
{
	//set data
	for (unsigned char i = 0; i < 3; i++)
	{
		_renderData.push_back(shapeInfo.points[i].locationData.getX());
		_renderData.push_back(shapeInfo.points[i].locationData.getY());
		_renderData.push_back(shapeInfo.points[i].locationData.getZ());

		_renderData.push_back(shapeInfo.points[i].colorData.get(0));
		_renderData.push_back(shapeInfo.points[i].colorData.get(1));
		_renderData.push_back(shapeInfo.points[i].colorData.get(2));

		_renderData.push_back(shapeInfo.points[i].texturePosData.get(0));
		_renderData.push_back(shapeInfo.points[i].texturePosData.get(1));
	}

	hasChange = true;

	return canvas_shape(_nodeBuffer, &_renderData.at(_renderData.size() - 24));
}