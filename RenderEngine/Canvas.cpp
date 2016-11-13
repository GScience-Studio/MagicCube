
#include "Canvas.h"
#include "Camera.h"

void canvas::addShapes(const void* data, unsigned int size)
{
	for (unsigned int i = 0; i < size; i++)
		_renderData.push_back(((GLfloat*)data)[i]);

	_hasChange = true;
}
void canvas::addShapes(canvas_shape* shapeInfo, unsigned int count)
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
	_glInstance.useBuffer(*_getBuffer());
	_glInstance.useShaderProgram(*_getShaderProgram());
	_glInstance.useTexture(*_getTexture());

	if (_hasChange)
	{
		_hasChange = false;

		_refreshShape();
	}

	if (_renderData.size() == 0)
		return;

	_getShaderProgram()->setCamera(_golbalCamera + _nodeCamera, _modelLocation);

	_glInstance.draw(0, _renderData.size() / 8);
}
void canvas::_refreshShape()
{
	if (_glInstance.bufferResize(*_getBuffer(), _renderData.capacity() * sizeof(GLfloat)))
		_lastVectorSize = 0;

	if (_renderData.size() != 0)
		_getShaderProgram()->setBufferData(&_renderData.at(0), _lastVectorSize * sizeof(GLfloat), _renderData.size() * sizeof(GLfloat), *_getBuffer());

	_lastVectorSize = _renderData.size();
}