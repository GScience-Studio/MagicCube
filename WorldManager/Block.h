#pragma once

#include <stdint.h>

class block 
{
private:
	uint16_t _blockInfo = 0;

public:
	uint16_t getBlockID()
	{
		return _blockInfo << 4 >> 4;
	}
	uint8_t getBlockLight()
	{
		return _blockInfo >> 12;
	}
	//Block ID can't large than 4096
	void setBlockID(uint16_t blockID)
	{
		_blockInfo = _blockInfo >> 12 << 12;
		_blockInfo += blockID;
	}
	//Light can't large than 16
	void setBlockLight(uint8_t light)
	{
		_blockInfo = _blockInfo << 4 >> 4;
		_blockInfo += light;
	}
};