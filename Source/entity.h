#pragma once
#include "raylib.h"

class Entity
{
private:
public:
	int maxHealth = 100;
	int health = maxHealth;
	Vector2 pos{ 0.f,0.f };
	Rectangle hitBox{ 0.f,0.f,0.f,0.f };

	virtual bool GetHit(Vector2 sourcePos, int potentialDamage) 
	{
		(void)sourcePos;
		(void)potentialDamage;
		return true; 
	}
	virtual Vector2 GetCenter() { return Vector2(0.f, 0.f); };
	virtual void LoseAdvantage(){};
	virtual bool GetLookSide() {return false;}
};