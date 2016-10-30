#pragma once

#include "ExtensionManager.h"
#include "FPSControllerManager.h"
#include "Application.h"

class fps_controller_extension :public extension
{
public:
	fps_controller_extension() :extension(std::string("FPSControllerExtension")) {}

	void init();
};