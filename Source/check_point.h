#pragma once
#include "raylib.h"
#include "entity.h"
#include <cmath>

class CheckPoint
{
private:
	float dist = 0.f;
	float range = 2.f;
	bool inRange = false;
	bool activated = false;
	Vector2 pos{ 0.f,0.f };
	Entity* playerRef = nullptr;
public:
	void SetActivated(bool newValue) { activated = newValue; }
	bool GetActivated() { return activated; }
	Vector2 GetPos() { return pos; }
	void Setup(Vector2 newPos, Entity& ref);
	bool Update(float dt);
	void Render();
};