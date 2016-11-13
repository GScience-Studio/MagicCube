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
	size_vec(unsigned int width, unsigned int height) :vec( { width, height } ) {}

	unsigned int getHeight() const
	{
		return data[1];
	}
	unsigned int getWidth() const
	{
		return data[0];
	}

	void setHeight(unsigned int height)
	{
		data[1] = height;
	}
	void setWidth(unsigned int width)
	{
		data[0] = width;
	}
};