#pragma once

#include "ExtensionManager.h"
#include "FPCManager.h"
#include "Application.h"

//第一人称控制器扩展
class fpc_extension :public extension
{
public:
	fpc_extension() :extension(std::string("FPCExtension")) {}
};