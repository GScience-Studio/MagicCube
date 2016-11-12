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
		chunkRenderShader = new chunk_render_shader();

		gl_manager::getInstance().genShader("ChunkRender.vert", "ChunkRender.frag", "ChunkRender.gs", chunkRenderShader);
	}
};