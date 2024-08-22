#include "game.h"

Game::Game()
{
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Unholy Trek");
	InitAudioDevice();
	SetTargetFPS(60);
	Image icon = LoadImage("Assets/Icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		sceneManager.Update();
	}
}

Game::~Game()
{
	CloseAudioDevice();
	CloseWindow();
}
