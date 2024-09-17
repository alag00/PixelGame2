#include "game.h"

Game::Game()
{
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Unholy Trek");
	InitAudioDevice();
	//SetTargetFPS(60);
	Image icon = LoadImage("Assets/Icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
	HideCursor();

	int monitor = GetCurrentMonitor();
	if (GetMonitorWidth(monitor) == screenWidth && GetMonitorHeight(monitor) == screenHeight)
	{
		ToggleFullScreenWindow(screenWidth, screenHeight);
	}
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		sceneManager.Update();
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

Game::~Game()
{
	CloseAudioDevice();
	CloseWindow();
}
