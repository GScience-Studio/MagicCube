#include "ChunkManager.h"

chunk_manager::chunk_manager(int visualFieldSize)
{
	size = visualFieldSize;
	ArraySize = visualFieldSize*visualFieldSize;

	chunks = new chunk[ArraySize];
}

chunk::chunk(int x,int z)
{
	cx = x;
	cz = z;

	wx = x * 16;
	wz = x * 16;

	blocks = new block[16, 256, 16];
}

void chunk::build()
{
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				//blocks[x,y,z]=xxxblock;
			}
		}
	}
}

