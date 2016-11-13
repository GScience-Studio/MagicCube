#pragma once

#include "RenderEngine.h"
#include "SceneNode.h"
#include "Camera.h"

class scene_node_manager
{
private:
	//scene list
	std::vector<scene_node*> _sceneList;

	scene_node* _nowScene	= nullptr;
	scene_node* _nextScene	= nullptr;

	//scene lock
	std::mutex lock;

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
			if (_nextScene != nullptr)
				_nowScene = _nextScene;
			else
				return;

		if (_nextScene != nullptr)
		{
			//play scene changing
			_nowScene = _nextScene;

			_nextScene = nullptr;
		}
		else
		{
			//refresh scene
			_nowScene->sceneTickCall();
		}

		if (draw)
		{
			lock.lock();

			_nowScene->_draw(_globalCamera);

			lock.unlock();
		}
	}

public:
	//add an scene
	scene_node* addScene(scene_node* scene)
	{
		lock.lock();

		_sceneList.push_back(scene);

		lock.unlock();

		return scene;
	}
	//add an scene with no tick function
	scene_node* addScene()
	{
		lock.lock();

		_sceneList.push_back(new scene_node);

		lock.unlock();

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
		_nextScene = scene;
	}
	~scene_node_manager()
	{
		for (auto screen : _sceneList)
		{
			delete(screen);
		}
	}
};