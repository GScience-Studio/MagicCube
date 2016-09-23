#pragma once

#include <vector>

#include "RenderEngine.h"
#include "RenderNodeManager.h"
#include "RenderNode.h"

class scene :public render_node_manager
{
	friend class scene_manager;

	//save the list that gen in this scene
	render_node_list _renderNodeList;

	//draw a scene
	void _draw()
	{
		//check all render node
		for (auto& renderNode : _renderNodeList)
		{
			(renderNode)->_draw();
		}
	}

public:
	~scene()
	{
		//free
		for (auto* renderNode : _renderNodeList)
		{
			delete(renderNode);
		}
	}
	//add an render node by user
	void addRenderNode(const render_node& renderNode)
	{
		_renderNodeList.push_front(new render_node(renderNode));
	}
	//add canvas
	canvas* addCanvas()
	{
		return _addCanvas(_renderNodeList);
	}
};
class scene_manager
{
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
	void _sceneRefreshAndDraw()
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