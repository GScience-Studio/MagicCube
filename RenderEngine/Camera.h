#pragma once

#include "RenderEngine.h"

class angle:private vec<float, 2>
{
private:
	std::mutex	_lock;

public:
	angle(float posX, float posY) :vec<float, 2>({ posX, posY }) {}

	angle(const angle& angle) :vec<float, 2>({ angle.get(0), angle.get(1) }) {}

	float getPosX()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return get(0);
	}
	float getPosY()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return get(1);
	}
	void setPosX(float posX)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[0] = posX;
	}
	void setPosY(float posY)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[1] = posY;
	}
	void rotateTo(float posX, float posY)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[0] = posX;
		data[1] = posY;
	}
	void rotate(float posX, float posY)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

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
/*
* location
* thread safety:can be call in all thread
* made by GM2000
*/
template<class T> class location :private vec<T, 3>
{
private:
	std::mutex	_lock;

public:
	location operator +(location loc)
	{
		return location<T>(get(0) + loc[0], get(1) + loc[1], get(2) + loc[2]);
	}
	location operator -(location loc)
	{
		return location<T>(-get(0), -get(1), -get(2));
	}
	location(T x, T y, T z) :vec<T, 3>({ x, y, z }) {}
	location(const location& angle) :vec<T, 3>({ angle.get(0), angle.get(1), angle.get(2) }) {}

	T getX()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return get(0);
	}
	T getY()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return get(1);
	}
	T getZ()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return get(2);
	}
	void setX(T x)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[0] = x;
	}
	void setY(T y)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[1] = y;
	}
	void setZ(T z)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[2] = z;
	}
	void move(T x, T y, T z)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[0] += x;
		data[1] += y;
		data[2] += z;
	}
	void moveTo(T x, T y, T z)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		data[0] = x;
		data[1] = y;
		data[2] = z;
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