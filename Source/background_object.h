#pragma once
#include "raylib.h"

class BackgroundObject
{
private:
	Vector2 pos{ 0.f,0.f };
	Texture2D txr{};
	Vector2 size{ 0.f,0.f };
public:
	~BackgroundObject();
	void Setup(Vector2 newPos);
	void SetTextue(Texture2D newTxr);
	void Render();
};