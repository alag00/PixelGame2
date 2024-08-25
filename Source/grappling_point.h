#pragma once
#include "raylib.h"
#include "entity.h"
#include <cmath>
#include "config.h"

class GrapplingPoint
{
private:
	float dist = 0.f;
	float range = 10.f;
	bool inRange = false;
	bool isIdeal = false;

	Vector2 pos{ 0.f,0.f };
	Entity* playerRef = nullptr;
	Config config;
public:
	void SetIdeal(bool newValue) { isIdeal = newValue; }
	bool GetIdeal() { return isIdeal; }
	float GetDistance() { return dist; }
	bool GetInRange() { return inRange; }
	Vector2 GetPos() { return pos; }
	void Setup(Vector2 newPos, Entity& ref);
	void Update();
	void Render();
};