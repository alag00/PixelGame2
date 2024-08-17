#include "background.h"


void Background::Unload()
{
	for (int i = 0; i < 3; i++)
	{
		UnloadTexture(caveTxr[i]);
		UnloadTexture(plainTxr[i]);
		UnloadTexture(castleFrontTxr[i]);
		UnloadTexture(castleTxr[i]);
		UnloadTexture(activeTxr[i]);
	}
}
void Background::Setup()
{
	castleTxr[0] = LoadTexture("Assets/BackgroundTextures/CastleBackground1.png");
	castleTxr[1] = LoadTexture("Assets/BackgroundTextures/CastleBackground2.png");
	castleTxr[2] = LoadTexture("Assets/BackgroundTextures/CastleBackground3.png");


	castleFrontTxr[0] = LoadTexture("Assets/BackgroundTextures/CastleEntranceBackground1.png");
	castleFrontTxr[1] = LoadTexture("Assets/BackgroundTextures/CastleEntranceBackground2.png");
	castleFrontTxr[2] = LoadTexture("Assets/BackgroundTextures/CastleEntranceBackground3.png");

	plainTxr[0] = LoadTexture("Assets/BackgroundTextures/PlainBackground1.png");
	plainTxr[1] = LoadTexture("Assets/BackgroundTextures/PlainBackground2.png");
	plainTxr[2] = LoadTexture("Assets/BackgroundTextures/PlainBackground3.png");

	caveTxr[0] = LoadTexture("Assets/BackgroundTextures/CaveBackground1.png");
	caveTxr[1] = LoadTexture("Assets/BackgroundTextures/CaveBackground2.png");
	caveTxr[2] = LoadTexture("Assets/BackgroundTextures/CaveBackground3.png");
}
void Background::SetLevelBackground(int level)
{
	switch (level)
	{
	case 1:
		activeTxr[0] = caveTxr[0];
		activeTxr[1] = caveTxr[1];
		activeTxr[2] = caveTxr[2];
		break;
	case 2:
		activeTxr[0] = plainTxr[0];
		activeTxr[1] = plainTxr[1];
		activeTxr[2] = plainTxr[2];
		break;
	case 3:
		activeTxr[0] = castleFrontTxr[0];
		activeTxr[1] = castleFrontTxr[1];
		activeTxr[2] = castleFrontTxr[2];
		break;
	case 4:
		activeTxr[0] = castleTxr[0];
		activeTxr[1] = castleTxr[1];
		activeTxr[2] = castleTxr[2];
		break;
	}
}
void Background::SetSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;

	txr2pos[1].x = -screenWidth;
	txr2pos[2].x = screenWidth;

	txr3pos[1].x = -screenWidth;
	txr3pos[2].x = screenWidth;
}

void Background::Update(Vector2 vel)
{
	if (vel.x == 0.f && vel.y == 0.f)
	{
		return;
	}

	txr2pos[0].x -= vel.x / 10.f;
	txr2pos[1].x -= vel.x / 10.f;
	txr2pos[2].x -= vel.x / 10.f;

	CheckPos(txr2pos[0].x);
	CheckPos(txr2pos[1].x);
	CheckPos(txr2pos[2].x);
	//pos2.y += vel.y;

	txr3pos[0].x -= vel.x / 5.f;
	txr3pos[1].x -= vel.x / 5.f;
	txr3pos[2].x -= vel.x / 5.f;

	CheckPos(txr3pos[0].x);
	CheckPos(txr3pos[1].x);
	CheckPos(txr3pos[2].x);
	//pos3.y += vel.y * 2.f;
}
void Background::Render()
{
	Rectangle src{ 0, 0, activeTxr[0].width, activeTxr[0].height };
	Rectangle dst{ 0, 0, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[0], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);


	dst = { txr2pos[0].x, txr2pos[0].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr2pos[1].x, txr2pos[1].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr2pos[2].x, txr2pos[2].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[1], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);


	dst = { txr3pos[0].x, txr3pos[0].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr3pos[1].x, txr3pos[1].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

	dst = { txr3pos[2].x, txr3pos[2].y, (float)screenWidth, (float)screenHeight };
	DrawTexturePro(activeTxr[2], src, dst, Vector2(0.f, 0.f), 0.f, WHITE);

}

void Background::CheckPos(float& xPos)
{
	if (xPos > screenWidth * 1.5f)
	{
		//float diff = xPos - screenWidth;
		xPos = -screenWidth * 1.5f;// +diff;
	}
	if (xPos < -screenWidth * 1.5f)
	{
		xPos = screenWidth * 1.5f;
	}
}