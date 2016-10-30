#pragma once

#include "RenderEngine.h"

class angle:private vec<float, 2>
{
public:
	angle(float posX, float posY) :vec<float, 2>({ posX, posY }) {}

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
	void rotate(float posX, float posY)
	{
		data[0] += posX;
		data[1] += posY;
	}

	angle operator +(angle inRotate)
	{
		return angle(inRotate.get(0) + get(0), inRotate.get(1) + get(1));
	}

	angle operator -(angle inRotate)
	{
		return angle(inRotate.get(0) - get(0), inRotate.get(1) - get(1));
	}
};
class camera
{
private:
	location<double>	_location;
	angle				_angle;
public:
	location<double>* getLocation()
	{
		return &_location;
	}
	angle* getAngle()
	{
		return &_angle;
	}
	camera(location<double> location, angle angle) :_location(location), _angle(angle) {}
	camera(double x, double y, double z, float posX, float posY) :_location(x, y, z), _angle(posX, posY) {}
	camera() :camera(0.0, 0.0, 0.0, 0.0f, 0.0f) {}

	camera operator +(const camera& inCamera)
	{
		return camera(_location + inCamera._location, _angle + inCamera._angle);
	}

	camera operator -(const camera& inCamera)
	{
		return camera(_location - inCamera._location, _angle - inCamera._angle);
	}
};