#pragma once

#include "enemy.h"
#include <cmath>
#include "animation.h"


class KnightEnemy : public Enemy
{
	Entity* playerRef = nullptr;
	Vector2 size{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };

	Animator anim;
	Texture2D idleAtlas{};
	Texture2D deathAtlas{};
	Texture2D walkAtlas{};
	Texture2D attack1Atlas{};
	Texture2D attack2Atlas{};
	Texture2D blockAtlas{};

	

	DECISION dec = DECISION::IDLE;
	float scale = 3.f;
	float distance = 0.f;
	float speed = 5.f;
	bool lookRight = false;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };

	bool hasAdvantage = true;
	int switchAgroCounter = 2;

	int currentAttackId = 1;
	int lastAttackId = 0;

	Vector2 leftBorder{ 0.f,0.f };
	Vector2 rightBorder{0.f,0.f};

	float lDist = 0.f;
	float rDist = 0.f;

	int currentSlice = 1;
	//bool isAlive = true;
public:
	~KnightEnemy();
	void SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D walkTxr, Texture2D attack1Txr, Texture2D attack2Txr, Texture2D blockTxr);
	void SetPlayerRef(Entity& ref) { playerRef = &ref; }
	void Setup();
	void Sense();
	void Decide();
	void Act(float dt);

	void Render();
	void CollisionCheck();

	void Walk(float dt);
	void Attack(float dt);

	void UpdateAgroSwitch();

	bool GetHit(Vector2 sourcePos, int potentialDamage, int id);

	void RenderUI();

	void Reset();
};