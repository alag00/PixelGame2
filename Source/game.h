#pragma once

#include "raylib.h"
#include "scene_manager.h"
#include "pause_menu.h"

class Game
{
private:
	int screenWidth = 1920;
	int screenHeight = 1080;
	SceneManager sceneManager;

	bool isRunning = true;

	PauseMenu pauseMenu;
	bool isPaused = false;
public:
	Game();
	void Run();
	void ToggleFullScreenWindow(int width, int height);
	void CheckToggleWindow();
	void TogglePause();
	~Game();
};