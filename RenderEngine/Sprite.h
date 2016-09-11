#pragma once

#include "RenderEngine.h"
#include "GLManager.h"

struct sprite_info
{
	//buffer info
	buffer drawBuffer = buffer();

	//address in vbo
	void* bufferAddress = NULL;

	sprite_info() {}
	sprite_info(buffer buffer, void* address):drawBuffer(buffer), bufferAddress(address) {}
};

struct sprite
{
	sprite_info* spriteInfos;

	sprite(sprite_info* spriteInfoArray, unsigned int count)
	{
		spriteInfos = new sprite_info[count];

		memcpy(spriteInfos, spriteInfoArray, count);
	}
	sprite(unsigned int count, sprite_info...)
	{
		spriteInfos = new sprite_info[count];

		va_list arg_ptr;
		__crt_va_start(arg_ptr, count);

		for (unsigned short i = 0; i<count; i++)
		{
			spriteInfos[i] = __crt_va_arg(arg_ptr, sprite_info);
		}
		__crt_va_end(arg_ptr);
	}
	~sprite()
	{
		delete[]spriteInfos;
	}
};