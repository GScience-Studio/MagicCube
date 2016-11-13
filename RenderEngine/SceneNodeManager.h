#pragma once

#include "RenderEngine.h"
#include "SceneNode.h"
#include "Camera.h"

#include <atomic>

class scene_node_manager
{
private:
	//scene list
	std::vector<scene_node*> _sceneList;

	scene_node* _nowScene	= nullptr;
	scene_node* _nextScene	= nullptr;

	std::atomic_bool _showingScene = false;
	
	//get the scene now is shown or will be hide
	scene_node* _getNowScene() const
	{
		return _nowScene;
	}

	//get the scene that will be show after transition
	scene_node* _getNextScene() const
	{
		return _nextScene;
	}

protected:
	//gobal screen camera
	camera _globalCamera;

	//scene refresh and draw
	void _sceneRefreshAndDraw(bool draw)
	{
		//is there has a scene?
		if (_nowScene == nullptr)
			if (_nextScene != nullptr && _showingScene == true)
			{
				_nowScene = _nextScene;

				_showingScene = false;
			}
			else
				return;

		if (_nextScene != nullptr && _showingScene == true)
		{
			//play scene changing
			_nowScene = _nextScene;

			_nextScene = nullptr;

			_showingScene = false;
		}

		if (draw)
		{
			_nowScene->_draw(_globalCamera);
		}
	}

public:
	//add an scene
	scene_node* addScene(scene_node* scene)
	{
		_sceneList.push_back(scene);

		return scene;
	}
	//add an scene with no tick function
	scene_node* addScene()
	{
		_sceneList.push_back(new scene_node);

		return _sceneList.back();
	}
	//get camera
	camera* getGlobalCamera()
	{
		return &_globalCamera;
	}
	//show an scene
	void showScene(scene_node* scene)
	{
		while (_showingScene);

		_nextScene = scene;

		_showingScene = true;
	}
	~scene_node_manager()
	{
		for (auto screen : _sceneList)
		{
			delete(screen);
		}
	}
};