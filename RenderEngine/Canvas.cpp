
#include "Canvas.h"

void canvas::addShapes(const canvas_shape* shapeInfo, unsigned int count)
{
	//set data
	for (unsigned int i = 0; i < count; i++)
		for (unsigned char j = 0; j < 3; j++)
		{
			_renderData.push_back(shapeInfo[i].points[j].locationData.getX());
			_renderData.push_back(shapeInfo[i].points[j].locationData.getY());
			_renderData.push_back(shapeInfo[i].points[j].locationData.getZ());

			_renderData.push_back(shapeInfo[i].points[j].colorData.get(0));
			_renderData.push_back(shapeInfo[i].points[j].colorData.get(1));
			_renderData.push_back(shapeInfo[i].points[j].colorData.get(2));

			_renderData.push_back(shapeInfo[i].points[j].texturePosData.get(0));
			_renderData.push_back(shapeInfo[i].points[j].texturePosData.get(1));
		}

	_hasChange = true;
}
void canvas::clear()
{
	_renderData.clear();

	_lastVectorSize = 0;

	_hasChange = true;
}
void canvas::_draw(camera _golbalCamera)
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

	_shaderProgram->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

	_glInstance.draw(0, _renderData.size() / 8);
}
void canvas::_refreshShape()
{
	if (_glInstance.bufferResize(_buffer, _renderData.capacity() * sizeof(GLfloat)))
		_lastVectorSize = 0;

	if (_renderData.size() != 0)
		_shaderProgram->setBufferData(&_renderData.at(0), _lastVectorSize * sizeof(GLfloat), _renderData.size() * sizeof(GLfloat), _buffer);

	_lastVectorSize = _renderData.size();
}