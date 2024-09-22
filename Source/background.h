#pragma once

#include "raylib.h"

class Background
{
private:
	const static int BACKGROUND_AMOUNT = 3;

	Texture2D activeTxr[BACKGROUND_AMOUNT];
	Vector2 txr2pos[BACKGROUND_AMOUNT];
	Vector2 txr3pos[BACKGROUND_AMOUNT];

	int screenWidth = 0;
	int screenHeight = 0;
	const float SPEED_X = 300.f;
	const float SPEED_Y = 1.f;
	const float SPEED_FOREGROUND_BONUS = 2.f;

	Vector2 lastCamPos = { 0.f,0.f };
public:
	void Unload();
	
	void SetLevelBackground(Texture2D newTxr[]);

	void SetSize(int width, int height);
	
	void Update(Vector2 newCamPos, float dt);
	
	void Render();

	void CheckPos(float& xPos);
	
};