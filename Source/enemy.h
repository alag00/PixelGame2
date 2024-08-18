#pragma once

#include "raylib.h"
#include "entity.h"

enum DECISION {
	IDLE,
	WALK,
	ATTACK,
	DAMAGED,
	PUSH,
	RANGED,
	LOSTADVANTAGE,
};

class Enemy : public Entity
{
private:
	float timer = 0.f;
	float refreshRate = 0.1f;
	bool isAlive = true;

public:
	bool isBoss = false;
	Vector2 startPos{ 0.f,0.f };
	void SetStartPos(Vector2 newPos) { startPos = newPos; pos = startPos; }
	virtual void SetPlayerRef(Entity& ref) { ref; }
	virtual void Setup(){};

	virtual void Sense(){};
	virtual void Decide(){};
	virtual void Act(float dt) { (void)dt; };

	void Update(float dt);
	virtual void Render(){};


	virtual bool GetHit(Vector2 sourcePos, int potentialDamage, int id) 
	{ 
		(void)sourcePos;
		(void)potentialDamage;
		(void)id;
		return true; 
	};

	void SetIsAlive(bool newValue) { isAlive = newValue; }
	bool IsAlive() { return isAlive; }
	virtual void RenderUI(){};

	virtual void Reset(){};
};