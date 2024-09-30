#pragma once
#include "entity.h"
#include "raylib.h"
#include <cmath>

class HurtBlock
{
private:
	bool activated = false;
	bool instakill = false;

	Entity* playerRef = nullptr;
	Vector2 oriPos = { 0.f,0.f };
	Vector2 centerPos = { 0.f,0.f };
	const float CENTER_OFFSET = 0.5f;
	const float EDGE_OFFSET = 0.3f;
	const float MIN_ACTIVATION_DIST = 1.f;
	const float HIT_PEAK_OFFSET = 0.2f;

	Rectangle hitBox{ 0.f,0.f,0.f,0.f };
	Vector2 lPos = {0.f,0.f };
	Vector2 mPos = { 0.f,0.f };
	Vector2 rPos = {0.f,0.f };
	const int TICK_DAMAGE = 10;


public:
	Vector2 GetPos() { return oriPos; }
	void Setup(Vector2 newPos, Entity& ref);
	bool Update();
	bool CollisionCheck();
	//bool LineBoxCheck(Vector2 l1, Vector2 l2, Rectangle box);
	void Render();
	float GetDist(Vector2 vec1, Vector2 vec2);

	void SetInstakill(bool newValue) { instakill = newValue; }
	bool GetInstakill() { return instakill; }
	void SetActivated(bool newValue) { 

		activated = newValue; 
	
	}
};

// PLANS:
/*
* 
* hURTBLOCK HAS bool for instakill or tickdamage
* during setuptile() if D set instakill bool to true, if H set instakill bool to false
* when player collides with D or H tiles, miscManager.GetHurtBlock(x,y).SetActive(true);
* active D, H tiles check distance from player, if distance is too far, set active to false;
*/