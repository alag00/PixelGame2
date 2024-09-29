#pragma once
#include "scene.h"
#include "main_menu.h"
#include "level_manager.h"
#include "developer_scene.h"

class SceneManager {
private:
	Scene* currentScene = nullptr;
public:
	SceneManager();
	~SceneManager();
	void Setup();
	void Update();
	void ChangeScene(SCENE_TYPE sceneType);

};