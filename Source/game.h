#pragma once

#include "raylib.h"
#include "scene_manager.h"

class Game
{
private:
	int screenWidth = 1080;
	int screenHeight = 760;
	SceneManager sceneManager;
public:
	Game();
	void Run();
	~Game();
};