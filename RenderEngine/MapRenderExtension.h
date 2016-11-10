#pragma once

#include "ExtensionManager.h"
#include "MapRender.h"
#include "MapRenderShader.h"
#include "Application.h"

class map_render_extension :public extension
{
public:
	map_render_extension() :extension("MapRenderExtension") {}

	void init()
	{
		mapRenderShader = new map_render_shader();

		gl_manager::getInstance().genShader("MapRender.vert", "MapRender.frag", "MapRender.gs", mapRenderShader);
	}
};