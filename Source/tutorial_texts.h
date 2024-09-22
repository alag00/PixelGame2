#pragma once

#include "text_render.h"
#include "raylib.h"
#include "config.h"
#include "entity.h"
#include <cmath>

class Tutorial
{
private:
	Entity* playerRef = nullptr;
	Config config;
	Vector2 textPos[3];
	TextRenderer txtRend;
	const int FONT_SIZE = 30;
public:
	void SetPlayerRef(Entity& ref);
	void Setup(Vector2 pos, int index);
	void Render();
	float GetDist(Vector2 pos1, Vector2 pos2);
};