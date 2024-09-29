#include "developer_scene.h"

void DeveloperScene::LoadScene()
{
	screenWidth = (float)GetScreenWidth();
	screenHeight = (float)GetScreenHeight();

	devNameTxr = LoadTexture("Assets/MainMenu/DevName.png");
	atlas = LoadTexture("Assets/MainMenu/DevAtlas.png");
	anim.SetAnimation(atlas, 11, false);
	anim.CustomFPS(CUSTOM_FPS);

	dst.width = SIZE_IN_PIXELS * SCALE;
	dst.height = SIZE_IN_PIXELS * SCALE;

	dst.x = (screenWidth / 2.f) - (dst.width / 2.f);
	dst.y = (screenHeight / 2.f) - (dst.height / 2.f);

	nameDst = dst;
	nameDst.height /= 2.f;
	nameDst.y += dst.height;

	cam.offset = { screenWidth / 2.f, screenHeight / 2.f };
	cam.target = { screenWidth / 2.f, screenHeight / 2.f };
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	filter.Setup(cam, (int)screenWidth, (int)screenHeight);
	filter.StartEffect(FADE_FROM_BLACK);
}
void DeveloperScene::LeaveScene()
{
	UnloadTexture(atlas);
}
bool DeveloperScene::Update()
{
	// Check when to change scene

	float dt = GetFrameTime();
	
	filter.Update(dt);
	startTimer -= dt;
	if (startTimer > 0.f)
	{
		return false;
	}

	anim.UpdateAnimator(dt);

	if (!endScene && anim.GetCurrentFrame() >= 10)
	{
		ChangeToMainMenu();
		endScene = true;
		filter.StartEffect(FADE_TO_BLACK);
	}
	return CheckEvent();

}
void DeveloperScene::Render()
{
	// Render
	BeginDrawing();
	ClearBackground(BACKGROUND_COLOR);

	Vector2 origin = { 0.f,0.f };
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	Rectangle src = { 0.f, 0.f, (float)devNameTxr.width, (float)devNameTxr.height };
	DrawTexturePro(devNameTxr, src, nameDst, origin, 0.f, WHITE);

	filter.Render();
	EndDrawing();

}

bool DeveloperScene::CheckEvent()
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