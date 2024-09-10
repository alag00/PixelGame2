#pragma once

#include "raylib.h"

class Background
{
private:
	/*
	Texture2D caveTxr[3];
	Texture2D plainTxr[3];
	Texture2D castleFrontTxr[3];
	Texture2D castleTxr[3];
	*/
	Texture2D activeTxr[3];

	Vector2 txr2pos[3];

	Vector2 txr3pos[3];

	int screenWidth = 0;
	int screenHeight = 0;
	float xSpeed = 300.f;
	float ySpeed = 1.f;

	Vector2 lastCamPos = { 0.f,0.f };
public:
	void Unload();
	
	//void Setup();
	
	//void SetLevelBackground(int level);
	void SetLevelBackground(Texture2D newTxr[]);

	void SetSize(int width, int height);
	
	void Update(Vector2 newCamPos, float dt);
	
	void Render();

	void CheckPos(float& xPos);
	
};