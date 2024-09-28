#pragma once
#include "entity.h"
#include "raylib.h"
#include <cmath>

class DeathBlock
{
private:
	Entity* playerRef = nullptr;
	Vector2 centerPos = { 0.f,0.f };
	const float CENTER_OFFSET = 0.5f;
	const float MIN_ACTIVATION_DIST = 1.f;
	const float HIT_PEAK_OFFSET = 0.2f;

	Rectangle hitBox{ 0.f,0.f,0.f,0.f };
	Vector2 lPos = {0.f,0.f };
	Vector2 mPos = { 0.f,0.f };
	Vector2 rPos = {0.f,0.f };
public:
	void Setup(Vector2 newPos, Entity& ref);
	bool Update();
	bool CollisionCheck();
	//bool LineBoxCheck(Vector2 l1, Vector2 l2, Rectangle box);
	void Render();
	float GetDist(Vector2 vec1, Vector2 vec2);
};