#include "main_menu.h"




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

