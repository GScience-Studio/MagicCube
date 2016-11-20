#pragma once

#include "ExtensionManager.h"
#include "NormalShader.h"

class normal_shader_extension :public extension
{
public:
	normal_shader_extension() :extension(std::string("NormalShaderExtension")) {}

	void init()
	{
		normal2DRenderProgram = new normal_2d_render_program();
		normal3DRenderProgram = new normal_3d_render_program();

		//load normal 3d shader
		gl_manager::getInstance().bindShader("Normal3d.vert", "Normal3d.frag", normal3DRenderProgram);

		//load normal 2d shader
		gl_manager::getInstance().bindShader("Normal3d.vert", "Normal3d.frag", normal2DRenderProgram);
	}
};