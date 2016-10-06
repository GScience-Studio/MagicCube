#pragma once

#include "RenderEngine.h"

class rotate :private vec<float, 2>
{
public:
	rotate(float posX, float posY) :vec<float, 2>({ posX, posY }) {}

	float getPosX() const
	{
		return get(0);
	}
	float getPosY() const
	{
		return get(1);
	}
	void setPosX(float posX)
	{
		data[0] = posX;
	}
	void setPosY(float posY)
	{
		data[1] = posY;
	}
	void rotateTo(float posX, float posY)
	{
		data[0] = posX;
		data[1] = posY;
	}

	rotate operator +(rotate inRotate)
	{
		return rotate(inRotate.get(0) + get(0), inRotate.get(1) + get(1));
	}
};
class camera
{
private:
	location<double>	_location;
	rotate				_rotate;
public:
	location<double>* getLocation()
	{
		return &_location;
	}
	rotate* getRotate()
	{
		return &_rotate;
	}
	camera(location<double> location, rotate rotate) :_location(location), _rotate(rotate) {}
	camera(double x, double y, double z, float posX, float posY) :_location(x, y, z), _rotate(posX, posY) {}
	camera() :camera(0.0, 0.0, 0.0, 0.0f, 0.0f) {}

	camera operator +(camera inCamera)
	{
		return camera(_location + inCamera._location, _rotate + inCamera._rotate);
	}
};