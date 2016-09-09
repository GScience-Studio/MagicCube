#pragma once

template<class T,unsigned char vecSize> class vec
{
	unsigned char size = vecSize;

	T data[vecSize];
public:
	vec(T firstData,T...)
	{
		T j = 0;

		va_list arg_ptr;
		__crt_va_start(arg_ptr, firstData);

		unsigned char count = 0;

		data[0] = firstData;

		for (int i=1;i<size;i++)
		{
			j = __crt_va_arg(arg_ptr, T);

			data[i]= j;
		}
		__crt_va_end(arg_ptr);
	}
	void get(unsigned char id)
	{
		return data[id];
	}
};

class size :public vec<unsigned int, 2>
{
public:
	size(unsigned int height, unsigned int width) :vec(height,width) {}
};