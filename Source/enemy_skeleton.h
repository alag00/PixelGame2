#pragma once

#include "enemy.h"
#include "animation.h"
#include <cmath>


class SkeletonEnemy : public Enemy
{
private:
	Texture2D idleAtlas{};
	Texture2D deathAtlas{};
	Texture2D attackAtlas{};
	Texture2D blockAtlas{};

	Entity* playerRef = nullptr;
	Animator anim;



	float scale = 3.f;
	Vector2 size{ 0.f,0.f };

	bool lookRight = false;
	float distance = 0.f;

	DECISION dec = DECISION::IDLE;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };

	int currentAttackId = 1;
	int lastAttackId = 0;

	float attackCooldown = 1.f;
	float attackTimer = attackCooldown;
public:

	~SkeletonEnemy();
	void SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D attackTxr, Texture2D blockTxr);
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