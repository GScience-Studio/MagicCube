
#include "Canvas.h"

void canvas::addShape(const canvas_shape& shapeInfo)
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
}
void canvas::clear()
{
	_renderData.clear();
	hasChange = true;
}