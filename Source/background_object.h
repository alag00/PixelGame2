#pragma once
#include "raylib.h"
#include "config.h"

class BackgroundObject
{
private:
	Vector2 pos{ 0.f,0.f };
	Texture2D txr{};
	Vector2 size{ 0.f,0.f };
	Config config;
	const float PIXEL_SCALE = 4.f;
	const float OFFSET_X = 0.5f;
	const float OFFSET_Y = 1.f;
	const float PIXELS_PER_TILE = 16;
	const float HALF_OF_TILE = 32;
	Rectangle src{ 0.f,0.f,0.f,0.f };
	Rectangle dst{ 0.f,0.f,0.f,0.f };
public:
	~BackgroundObject();
	void Setup(Vector2 newPos);
	void SetTextue(Texture2D newTxr);
	void Render(Rectangle cam);
};