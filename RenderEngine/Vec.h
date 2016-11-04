#pragma once

#include <initializer_list>
#include <GLM\vec3.hpp>

template<class T,unsigned char vecSize> class vec
{
protected:
	T data[vecSize];

public:
	T& operator [](unsigned int pos)
	{
		return data[pos];
	}
	vec(std::initializer_list<T> dataList)
	{
		unsigned int i = 0;

		for (auto getData: dataList)
		{
			data[i] = getData;

			if (++i == vecSize)
				return;
		}
	}
	vec(T firstData[vecSize])
	{
		for (int i = 0; i<vecSize; i++)
		{
			data[i] = firstData[i];
		}
	}
	T get(unsigned char id) const
	{
		return data[id];
	}
	void set(unsigned char id, T value)
	{
		data[id] = value;
	}
};

//size(such as window size)
class size_vec :private vec<unsigned int, 2>
{
public:
	size_vec(unsigned int height, unsigned int width) :vec( {height,width} ) {}

	unsigned int getHeight() const
	{
		return get(0);
	}
	unsigned int getWidth() const
	{
		return get(1);
	}
};

//location
template<class T> class location :private vec<T, 3>
{
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

	T getX() const
	{
		return get(0);
	}
	T getY() const
	{
		return get(1);
	}
	T getZ() const
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