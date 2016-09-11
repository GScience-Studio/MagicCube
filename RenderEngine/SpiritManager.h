#pragma once

#include "GLManager.h"
#include "Spirit.h"

class spirit_manager
{
private:
	buffer		spiritBuffer;
	gl_manager& glInstance = gl_manager::getInstance();

protected:
	void initSpiritManager()
	{
		spiritBuffer = buffer(glInstance.genVAO(), glInstance.genVBO());
	}

public:
	spirit addSpirit(location<float> loc)
	{
		return spirit(1, 0);
	}
};