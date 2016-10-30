#pragma once

#include "ExtensionManager.h"
#include "NormalShader.h"

class normal_shader_extension :public extension
{
public:
	normal_shader_extension() :extension(std::string("NormalShaderExtension")) {}

	void init()
	{
		normal2DShader = new normal_2d_shader();
		normal3DShader = new normal_3d_shader();

		//load normal 3d shader
		gl_manager::getInstance().genShader("Normal3d.vert", "Normal3d.frag", normal3DShader);

		//load normal 2d shader
		gl_manager::getInstance().genShader("Normal3d.vert", "Normal3d.frag", normal2DShader);
	}
};