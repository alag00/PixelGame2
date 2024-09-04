#pragma once

#include "raylib.h"
#include "scene_manager.h"

class Game
{
private:
	int screenWidth = 1720;
	int screenHeight = 880;
	SceneManager sceneManager;
public:
	Game();
	void Run();
	void ToggleFullScreenWindow(int width, int height);
	~Game();
};