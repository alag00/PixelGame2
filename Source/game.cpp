#include "game.h"

Game::Game()
{
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(screenWidth, screenHeight, "The Unholy Trek");
	InitAudioDevice();
	SetTargetFPS(60);
	Image icon = LoadImage("Assets/Icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
	HideCursor();
	sceneManager.Setup();
	CheckToggleWindow();

	pauseMenu.Setup(isRunning, isPaused);
}

void Game::Run()
{
	while (isRunning)
	{
		if (IsKeyPressed(KEY_ESCAPE))
		{
			TogglePause();
		}
		if (!isPaused)
		{
			sceneManager.Update();
		}
		else
		{
			pauseMenu.Update();
		}
	}
}

void Game::ToggleFullScreenWindow(int width, int height)
{
	if (!IsWindowFullscreen())
	{
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
	else
	{
		ToggleFullscreen();
		SetWindowSize(width, height);
	}
}

void Game::CheckToggleWindow()
{
	int monitor = GetCurrentMonitor();
	if (GetMonitorWidth(monitor) == screenWidth && GetMonitorHeight(monitor) == screenHeight)
	{
		ToggleFullScreenWindow(screenWidth, screenHeight);
	}
}

void Game::TogglePause()
{
	isPaused = !isPaused;
	//CheckToggleWindow();
	if (isPaused)
	{
		ShowCursor();
	}
	else
	{
		HideCursor();
	}
}

Game::~Game()
{
	CloseAudioDevice();
	CloseWindow();
}
