#pragma once

#include "../RenderEngine/ChunkRender.h"

class chunk_manager {
public:
	chunk* chunks;

	chunk_manager(int visualFieldSize);

private:
	int size;
	int ArraySize;
};

class chunk {
public:
	int cx, cz, wx, wz;
	block* blocks;

	chunk(int x,int z);

	void build();
	void setChunkRender(chunk_render chunkrender);

private:

};

class block {
public:
	block() {};
};