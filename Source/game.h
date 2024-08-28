#pragma once

#include "raylib.h"
#include "scene_manager.h"

class Game
{
private:
	int screenWidth = 1920;
	int screenHeight = 1080;
	SceneManager sceneManager;
public:
	Game();
	void Run();
	void ToggleFullScreenWindow(int width, int height);
	~Game();
};