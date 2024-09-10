#include "main_menu.h"

/*
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
*/


void MainMenu::LoadScene()
{

}

void MainMenu::LeaveScene()
{
	UnloadTexture(bg);
}
bool MainMenu::Update()
{
	if (!isTxrLoaded)
	{
		LoadTextures();
	}
	if (IsKeyPressed(KEY_SPACE))
	{
		nextScene = SCENE_TYPE::LEVEL;
		return true;
	}
	
	return false;
}
void MainMenu::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawBackground();

	DrawText("Press 'Space'", 80, GetScreenHeight() - 80, 40, YELLOW);

	EndDrawing();
}
void MainMenu::RenderUI()
{

	


}

void MainMenu::DrawBackground()
{
	Rectangle src{ 0.f,0.f, (float)bg.width, (float)bg.height };
	Rectangle dst{ 0.f,0.f,(float)GetScreenWidth(), (float)GetScreenHeight() };
	Vector2 ori{ 0.f,0.f };
	DrawTexturePro(bg, src, dst, ori, 0.f, WHITE);
}

void MainMenu::LoadTextures()
{
	bg = LoadTexture("Assets/BackgroundTextures/Skybackground1.png");
	isTxrLoaded = true;
}

