#pragma once

#include "ExtensionManager.h"
#include "FPCManager.h"
#include "Application.h"

//��һ�˳ƿ�������չ
class fpc_extension :public extension
{
public:
	fpc_extension() :extension(std::string("FPCExtension")) {}
};