#include "main_menu.h"




void MainMenu::LoadScene()
{
	screenWidth = (float)GetScreenWidth();
	screenHeight = (float)GetScreenHeight();

	bg = LoadTexture("Assets/MainMenu/AnimatedBackgroundAtlas.png");
	title = LoadTexture("Assets/MainMenu/MainTitle.png");

	menuSong = LoadMusicStream("Assets/Audio/Music/CutsceneTheme.mp3");
	PlayMusicStream(menuSong);

	anim.CustomFPS(backgroundFPS);
	anim.SetAnimation(bg, 4, true);

	cam.offset = { screenWidth / 2.f, screenHeight / 2.f };
	cam.target = { screenWidth / 2.f, screenHeight / 2.f };
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	filter.Setup(cam, (int)screenWidth, (int)screenHeight);
	filter.StartEffect(FADE_FROM_BLACK);
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
		endScene = true;
		filter.StartEffect(FADE_TO_BLACK);
	}
	
	float dt = GetFrameTime();
	filter.Update(dt);
	anim.UpdateAnimator(dt);
	blinkTimer += dt;
	if (blinkTimer >= BLINK_RATE)
	{
		blinkTimer = 0.f;
		showText = !showText;
	}

	return CheckEvent();
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
	filter.Render();
	EndDrawing();
}
void MainMenu::RenderUI()
{

	


}

void MainMenu::DrawBackground()
{
	Rectangle src{ 0.f,0.f, (float)bg.width, (float)bg.height };
	Rectangle dst{ 0.f,0.f,screenWidth, screenHeight };
	Vector2 ori{ 0.f,0.f };
	//DrawTexturePro(bg, src, dst, ori, 0.f, WHITE);
	anim.DrawAnimationPro(dst, ori, 0.f, WHITE);

	src = { 0.f, 0.f, (float)title.width, (float)title.height };
	dst = { 0.f,0.f, screenWidth / 2.f, screenHeight / 4.f };
	dst.x = dst.width - (dst.width / 2.f);
	dst.y = (screenHeight / 4.f) - (dst.height / 2.f);
	DrawTexturePro(title, src, dst, ori, 0.f, WHITE);
}

bool MainMenu::CheckEvent()
{
	if (!endScene)
	{
		return false;
	}
	if (filter.IsActive())
	{
		return false;
	}


	return true;

}

