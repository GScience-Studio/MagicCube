#pragma once

#include <algorithm>

#include "RenderEngine.h"

class extension
{
	friend class extension_manager;

protected:
	extension(std::string extensionName) :_extensionName(extensionName) {}

	std::string _extensionName = "";

public:
	virtual void init() {}
	virtual void unload() {}

	bool operator ==(const extension& extension)
	{
		return extension._extensionName == _extensionName;
	}
};

class extension_manager
{
private:
	std::vector<extension*> extensionList;

	bool _hasLoadExtension(extension* extension)
	{
		for (auto getExtension : extensionList)
			if (*getExtension == *extension)
			{
				delete(extension);

				return true;
			}

		return false;
	}
public:
	~extension_manager()
	{
		for (auto getExtension : extensionList)
		{
			getExtension->unload();

			delete(getExtension);
		}
	}
	bool hasLoadExtension(std::string extensionName)
	{
		for (auto getExtension : extensionList)
			if (getExtension->_extensionName == extensionName)
			{
				return true;
			}

		return false;
	}

	void loadExtension(extension* extension)
	{
		//check extension
		if (extension->_extensionName == "")
			message("[ERROR]fail to load extension,extension's name is empty", msgError, true);

		//has load?
		if (_hasLoadExtension(extension))
			return;

		//load
		extensionList.push_back(extension);

		extension->init();
	}
};
