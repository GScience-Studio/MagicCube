#pragma once

#include "ExtensionManager.h"
#include "ChunkRender.h"
#include "ChunkRenderShader.h"
#include "Application.h"

class chunk_render_extension :public extension
{
public:
	chunk_render_extension() :extension("ChunkRenderExtension") {}

	void init()
	{
		//load shader
		chunkRenderProgram = new chunk_render_program();

		gl_manager::getInstance().bindShader("ChunkRender.vert", "ChunkRender.frag", "ChunkRender.gs", chunkRenderProgram);
	}
};