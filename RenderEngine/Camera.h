#pragma once

#include "RenderEngine.h"

class angle : private vec<float, 2>
{
private:
	std::mutex	_lock;

public:
	angle(float posX, float posY) :vec<float, 2>({ posX, posY }) {}

	angle(const angle& angle) :vec<float, 2>({ angle.get(0), angle.get(1) }) {}

	float getPosX()
	{
		return get(0);
	}
	float getPosY()
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

class angle_synchronize : private vec<float, 2>
{
private:
	std::mutex	_lock;

public:
	angle_synchronize(float posX, float posY) :vec<float, 2>({ posX, posY }) {}

	angle_synchronize(const angle_synchronize& angle) :vec<float, 2>({ angle.get(0), angle.get(1) }) {}

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

	angle_synchronize operator +(angle_synchronize inRotate)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return angle_synchronize(inRotate.get(0) + get(0), inRotate.get(1) + get(1));
	}

	angle_synchronize operator -(angle_synchronize inRotate)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return angle_synchronize(inRotate.get(0) - get(0), inRotate.get(1) - get(1));
	}
	operator angle()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return angle(get(0), get(1));
	}
};
/*
* location
* thread safety:can be call only in event thread
* made by GM2000
*/
template<class T> class render_location :private vec<T, 3>
{
public:
	render_location operator +(render_location loc)
	{
		return render_location<T>(get(0) + loc[0], get(1) + loc[1], get(2) + loc[2]);
	}
	render_location operator -(render_location loc)
	{
		return render_location<T>(get(0) - loc.get(0), get(1) - loc.get(1), get(2) - loc.get(2));
	}
	render_location(T x, T y, T z) :vec<T, 3>({ x, y, z }) {}
	render_location(const render_location& inLocation) :vec<T, 3>({ inLocation.get(0), inLocation.get(1), inLocation.get(2) }) {}

	T getX()
	{
		return get(0);
	}
	T getY()
	{
		return get(1);
	}
	T getZ()
	{
		return get(2);
	}
	void setX(T x)
	{
		data[0] = x;
	}
	void setY(T y)
	{
		data[1] = y;
	}
	void setZ(T z)
	{
		data[2] = z;
	}
	void move(T x, T y, T z)
	{
		data[0] += x;
		data[1] += y;
		data[2] += z;
	}
	void moveTo(T x, T y, T z)
	{
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}
};
/*
* location
* thread safety:can be call in every thread
* made by GM2000
*/
template<class T> class location_synchronize :private vec<T, 3>
{
private:
	std::mutex	_lock;

public:
	location_synchronize operator +(location_synchronize loc)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return location_synchronize<T>(get(0) + loc[0], get(1) + loc[1], get(2) + loc[2]);
	}
	location_synchronize operator -(location_synchronize loc)
	{
		std::lock_guard<std::mutex> lockGuard(_lock);
		std::lock_guard<std::mutex> inLockGuard(loc._lock);
		
		return location_synchronize<T>(get(0) - loc.get(0), get(1) - loc.get(1), get(2) - loc.get(2));
	}
	location_synchronize(T x, T y, T z) :vec<T, 3>({ x, y, z }) {}
	location_synchronize(const location_synchronize& inLocation) :vec<T, 3>({ inLocation.get(0), inLocation.get(1), inLocation.get(2) }) {}

	operator render_location<T>()
	{
		std::lock_guard<std::mutex> lockGuard(_lock);

		return render_location<T>(get(0), get(1), get(2));
	}
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
	render_location<double>	_location;
	angle				_angle;

public:
	render_location<double>* getLocation()
	{
		return &_location;
	}
	angle* getAngle()
	{
		return &_angle;
	}

	camera(render_location<double> location, angle angle) :_location(location), _angle(angle) {}
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

	bool operator != (camera& inCamera)
	{
		return !(*this == inCamera);
	}
	bool operator == (camera& inCamera)
	{
		return this->getLocation()->getX() == inCamera.getLocation()->getX() &&
			this->getLocation()->getY() == inCamera.getLocation()->getY() &&
			this->getLocation()->getZ() == inCamera.getLocation()->getZ() &&
			this->getAngle()->getPosX() == inCamera.getAngle()->getPosX() &&
			this->getAngle()->getPosY() == inCamera.getAngle()->getPosY();
	}
};

class camera_synchronize
{
private:
	location_synchronize<double>	_location;
	angle_synchronize				_angle;

public:
	location_synchronize<double>* getLocation()
	{
		return &_location;
	}
	angle_synchronize* getAngle()
	{
		return &_angle;
	}

	camera_synchronize(location_synchronize<double> location, angle_synchronize angle) :_location(location), _angle(angle) {}
	camera_synchronize(double x, double y, double z, float posX, float posY) :_location(x, y, z), _angle(posX, posY) {}
	camera_synchronize() :camera_synchronize(0.0, 0.0, 0.0, 0.0f, 0.0f) {}

	camera_synchronize operator +(const camera_synchronize& inCamera)
	{
		return camera_synchronize(_location + inCamera._location, _angle + inCamera._angle);
	}

	camera_synchronize operator -(const camera_synchronize& inCamera)
	{
		return camera_synchronize(_location - inCamera._location, _angle - inCamera._angle);
	}

	operator camera()
	{
		return camera(_location, _angle);
	}
	bool operator != (camera_synchronize& inCamera)
	{
		return !(*this == inCamera);
	}
	bool operator == (camera_synchronize& inCamera)
	{
		return this->getLocation()->getX() == inCamera.getLocation()->getX() &&
			this->getLocation()->getY() == inCamera.getLocation()->getY() &&
			this->getLocation()->getZ() == inCamera.getLocation()->getZ() &&
			this->getAngle()->getPosX() == inCamera.getAngle()->getPosX() &&
			this->getAngle()->getPosY() == inCamera.getAngle()->getPosY();
	}
};