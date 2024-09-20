#pragma once
#include "raylib.h"
#include "entity.h"
#include <cmath>
#include "config.h"
#include "text_render.h"

class CheckPoint
{
private:
	float dist = 0.f;
	float range = 2.f;
	bool inRange = false;
	bool activated = false;
	Vector2 pos{ 0.f,0.f };
	Entity* playerRef = nullptr;
	Config config;
	TextRenderer txtRend;
	const float offsetToCenter = 0.5f;
	const float textOffset = 0.4f;
	const int textSize = 20;
public:
	void SetActivated(bool newValue) { activated = newValue; }
	bool GetActivated() { return activated; }
	Vector2 GetPos() { return pos; }
	void Setup(Vector2 newPos, Entity& ref);
	bool Update();
	void Render();
};