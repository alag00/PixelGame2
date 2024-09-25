#include "main_menu.h"




void MainMenu::LoadScene()
{
	screenWidth = (float)GetScreenWidth();
	sceenHeight = (float)GetScreenHeight();

	bg = LoadTexture("Assets/MainMenu/BackgroundPixelated.png");
	title = LoadTexture("Assets/MainMenu/MainTitle.png");

	menuSong = LoadMusicStream("Assets/Audio/Music/CutsceneTheme.mp3");
	PlayMusicStream(menuSong);
}

void MainMenu::LeaveScene()
{
	UnloadTexture(bg);
	UnloadTexture(title);

	UnloadMusicStream(menuSong);
}
bool MainMenu::Update()
{
	UpdateMusicStream(menuSong);
	if (IsKeyPressed(KEY_SPACE))
	{
		nextScene = SCENE_TYPE::LEVEL;
		return true;
	}
	float dt = GetFrameTime();
	blinkTimer += dt;
	if (blinkTimer >= BLINK_RATE)
	{
		blinkTimer = 0.f;
		showText = !showText;
	}

	return false;
}
void MainMenu::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawBackground();

	if (showText)
	{
		txtRend.RenderText("Press 'Space'", ((int)screenWidth / 2) - OFFSET, GetScreenHeight() - OFFSET, FONT_SIZE, YELLOW, BLACK);
	}
	//DrawText(CURRENT_VERSION, FONT_SIZE, GetScreenHeight() - FONT_SIZE, FONT_SIZE, YELLOW);
	txtRend.RenderText(CURRENT_VERSION, FONT_SIZE / 2, GetScreenHeight() - FONT_SIZE, FONT_SIZE, WHITE, BLACK);
	EndDrawing();
}
void MainMenu::RenderUI()
{

	


}

void MainMenu::DrawBackground()
{
	Rectangle src{ 0.f,0.f, (float)bg.width, (float)bg.height };
	Rectangle dst{ 0.f,0.f,screenWidth, sceenHeight };
	Vector2 ori{ 0.f,0.f };
	DrawTexturePro(bg, src, dst, ori, 0.f, WHITE);

	src = { 0.f, 0.f, (float)title.width, (float)title.height };
	dst = { 0.f,0.f, screenWidth / 2.f, sceenHeight / 4.f };
	dst.x = dst.width - (dst.width / 2.f);
	dst.y = (sceenHeight / 4.f) - (dst.height / 2.f);
	DrawTexturePro(title, src, dst, ori, 0.f, WHITE);
}

