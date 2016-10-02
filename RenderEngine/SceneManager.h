#pragma once

#include "RenderEngine.h"
#include "Scene.h"

class scene_manager
{
private:
	//scene list
	std::vector<scene> _sceneList;

	scene* _nowScene	= nullptr;
	scene* _nextScene	= nullptr;

	//get the scene now is shown or will be hide
	scene* _getNowScene() const
	{
		return _nowScene;
	}

	//get the scene that will be show after transition
	scene* _getNextScene() const
	{
		return _nextScene;
	}

protected:
	//scene refresh and draw
	void _sceneRefreshAndDraw(bool draw)
	{
		//is there has a scene?
		if (_nowScene == nullptr)
			if (_nextScene != nullptr)
				_nowScene = _nextScene;
			else
				return;

		//play scene changing
		if (_nextScene != nullptr)
		{
			_nowScene = _nextScene;

			_nextScene = nullptr;
		}

		if (draw)
			_nowScene->_draw();
	}

public:
	//add an scene
	scene* addScene()
	{
		_sceneList.push_back(scene());

		return &_sceneList.back();
	}

	//show an scene
	void showScene(scene* scene)
	{
		_nextScene = scene;
	}
};