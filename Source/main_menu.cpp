#include "main_menu.h"

void MainMenu::Setup(int w, int h)
{
	width = w; 
	height = h;
	bg = LoadTexture("Assets/BackgroundTextures/CastleBackground1.png");
}

bool MainMenu::Update() 
{
	if (IsKeyPressed(KEY_SPACE))
	{
		return false;
	}
	return true;
}

void MainMenu::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);

	Rectangle src{0.f,0.f, (float)bg.width, (float)bg.height};
	Rectangle dst{0.f,0.f,(float)width, (float)height};
	Vector2 ori{0.f,0.f};
	DrawTexturePro(bg, src, dst, ori, 0.f, WHITE);
	DrawText("Press 'Space'", 80, height - 80, 40, YELLOW);
	
	EndDrawing();
} 


void MainMenu::Unload() 
{
	UnloadTexture(bg);
}