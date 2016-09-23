#pragma once

template<class T,unsigned char vecSize> class vec
{
protected:
	T data[vecSize];

public:
	T operator [](unsigned int pos)
	{
		return data[pos];
	}
	vec(T firstData, T...)
	{
		T j = 0;

		va_list arg_ptr;
		__crt_va_start(arg_ptr, firstData);

		unsigned char count = 0;

		data[0] = firstData;

		for (int i = 1; i<vecSize; i++)
		{
			data[i] = __crt_va_arg(arg_ptr, T);
		}
		__crt_va_end(arg_ptr);
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
};

//size(such as window size)
class size_vec :private vec<unsigned int, 2>
{
public:
	size_vec(unsigned int height, unsigned int width) :vec(height,width) {}

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
	location(T x, T y, T z) :vec(x, y, z) {}

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
};