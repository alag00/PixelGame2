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

	Sound deathSound{};
	Sound initAttackSound{};
	Sound swingAttackSound{};

	Entity* playerRef = nullptr;
	Animator anim;



	float scale = 3.f;
	Vector2 size{ 0.f,0.f };

	bool lookRight = false;
	float distance = 0.f;

	DECISION dec = DECISION::IDLE;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };

	const short int ATTACK_DAMAGE = 10;
	const short int DEFLECTED_DAMAGE = 5;

	float attackCooldown = 1.f;
	float attackTimer = attackCooldown;

	float damagedTimer = 0.f;
public:

	~SkeletonEnemy();
	void SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D attackTxr, Texture2D blockTxr);
	void SetAudio(Sound death, Sound init, Sound swing);
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

	bool GetHit(Vector2 sourcePos, int potentialDamage);
	
	void RenderUI();

	void Reset();
};