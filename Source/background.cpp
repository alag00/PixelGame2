#include "background.h"


void Background::Unload()
{
	for (int i = 0; i < BACKGROUND_AMOUNT; i++)
	{
		UnloadTexture(activeTxr[i]);
	}
}

void Background::SetLevelBackground(Texture2D newTxr[])
{
	for (int i = 0; i < BACKGROUND_AMOUNT; i++)
	{
		activeTxr[i] = newTxr[i];
	}
}

void Background::SetSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	txr2pos[1].x = (float)-screenWidth;
	txr2pos[2].x = (float)screenWidth;

	txr3pos[1].x = (float)-screenWidth;
	txr3pos[2].x = (float)screenWidth;

}

void Background::Update(Vector2 newCamPos, float dt)
{
	Vector2 vel{ 0.f,0.f };
	vel.x = newCamPos.x - lastCamPos.x;
	vel.y = newCamPos.y - lastCamPos.y;
	lastCamPos = newCamPos;

	if (vel.x == 0.f && vel.y == 0.f)
	{
		return;
	}

	txr2pos[0].x -= vel.x * dt * SPEED_X;
	txr2pos[1].x -= vel.x * dt * SPEED_X;
	txr2pos[2].x -= vel.x * dt * SPEED_X;

	CheckPos(txr2pos[0].x);
	CheckPos(txr2pos[1].x);
	CheckPos(txr2pos[2].x);

	txr2pos[0].y -= vel.y * dt * SPEED_Y;
	txr2pos[1].y -= vel.y * dt * SPEED_Y;
	txr2pos[2].y -= vel.y * dt * SPEED_Y;

	txr3pos[0].x -= vel.x * dt * (SPEED_X * SPEED_FOREGROUND_BONUS);
	txr3pos[1].x -= vel.x * dt * (SPEED_X * SPEED_FOREGROUND_BONUS);
	txr3pos[2].x -= vel.x * dt * (SPEED_X * SPEED_FOREGROUND_BONUS);

	CheckPos(txr3pos[0].x);
	CheckPos(txr3pos[1].x);
	CheckPos(txr3pos[2].x);

	txr3pos[0].y -= vel.y * dt * (SPEED_Y * SPEED_FOREGROUND_BONUS);
	txr3pos[1].y -= vel.y * dt * (SPEED_Y * SPEED_FOREGROUND_BONUS);
	txr3pos[2].y -= vel.y * dt * (SPEED_Y * SPEED_FOREGROUND_BONUS);
}
void Background::Render()
{
	Rectangle src{ 0.f, 0.f, (float)activeTxr[0].width, (float)activeTxr[0].height };
	Rectangle dst{ 0.f, 0.f, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[0], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);


	dst = { txr2pos[0].x, txr2pos[0].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr2pos[1].x, txr2pos[1].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr2pos[2].x, txr2pos[2].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);


	//src = { 0.f, 0.f, (float)activeTxr[2].width, (float)activeTxr[2].height };
	dst = { txr3pos[0].x, txr3pos[0].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr3pos[1].x, txr3pos[1].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr3pos[2].x, txr3pos[2].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

}

void Background::CheckPos(float& xPos)
{
	float margin = 1.5f;
	if (xPos > screenWidth * margin)
	{
		xPos = -screenWidth * margin;
	}
	if (xPos < -screenWidth * margin)
	{
		xPos = screenWidth * margin;
	}
}

void Background::Reset()
{
	txr2pos[0].x = 0.f;
	txr2pos[1].x = (float)-screenWidth;
	txr2pos[2].x = (float)screenWidth;

	txr3pos[0].x = 0.f;
	txr3pos[1].x = (float)-screenWidth;
	txr3pos[2].x = (float)screenWidth;
}
