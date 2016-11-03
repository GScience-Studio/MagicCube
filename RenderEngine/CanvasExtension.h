#pragma once

#include "ExtensionManager.h"
#include "Canvas.h"
#include "CanvasTexture.h"
#include "ShapeCube.h"

class canvas_extension :public extension
{
public:
	canvas_extension() :extension(std::string("CanvasExtension")) {}
};