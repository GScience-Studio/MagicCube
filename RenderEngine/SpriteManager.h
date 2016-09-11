#pragma once

#include "GLManager.h"
#include "Sprite.h"

class sprite_manager
{
private:
	buffer		spriteBuffer;
	gl_manager& glInstance = gl_manager::getInstance();

protected:
	void initspriteManager()
	{
		spriteBuffer = buffer(glInstance.genVAO(), glInstance.genVBO());
	}

public:
	sprite addsprite(location<float> loc)
	{
		return sprite(1,sprite_info(buffer(2,0),0));
	}
};