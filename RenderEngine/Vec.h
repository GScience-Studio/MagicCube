#pragma once

template<class T,unsigned char vecSize> class vec
{
protected:
	T data[vecSize];

public:
	vec(T firstData, T...)
	{
		T j = 0;

		va_list arg_ptr;
		__crt_va_start(arg_ptr, firstData);

		unsigned char count = 0;

		data[0] = firstData;

		for (int i = 1; i<vecSize; i++)
		{
			j = __crt_va_arg(arg_ptr, T);

			data[i] = j;
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
	T _get(unsigned char id) const
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
		return _get(0);
	}
	unsigned int getWidth() const
	{
		return _get(1);
	}
};