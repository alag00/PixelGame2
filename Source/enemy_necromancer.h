#pragma once
#include "enemy.h"
#include "animation.h"
#include <cmath>
#include <vector>
#include "config.h"


class Projectiles : public Entity
{
private:
	Config config;
	Entity* playerRef = nullptr;
	float timeAlive = 2.f;
	int dir = 0;
	Vector2 size{ 0.f,0.f };
	Animator anim;
	float scale = 3.f;
	const short int ATTACK_DAMAGE = 10;
public:
	void Activate(Vector2 newPos);
	void Setup(Entity& ref, int direction, Texture2D txr, Vector2 newPos);
	void Update(float dt);
	void Render();
	void CollisionCheck();
	bool IsAlive();
};

class NecromancerEnemy : public Enemy
{
private:

	Texture2D idleAtlas{};
	Texture2D deathAtlas{};
	Texture2D meleeAttackAtlas{};
	Texture2D rangedAttackAtlas{};
	Texture2D blockAtlas{};
	Texture2D pushAtlas{};

	Texture2D projectileAtlas{};

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

	static const int projAmount = 2;
	Projectiles projList[projAmount];


	float attackCooldown = 1.f;
	float attackTimer = attackCooldown;

	float damagedTimer = 0.f;
public:

	~NecromancerEnemy();
	void SetPlayerRef(Entity& ref) { playerRef = &ref; }

	void SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D meleeTxr, Texture2D rangedTxr, Texture2D blockTxr, Texture2D pushTxr, Texture2D projTxr);
	void SetAudio(Sound death, Sound init, Sound swing);
	void Setup();
	void Sense();
	void Decide();
	void Act(float dt);


	void UpdateProj(float dt);
	void Render();
	void CollisionCheck();

	void RangedAttack();
	void Attack();

	void Push();

	bool GetHit(Vector2 sourcePos, int potentialDamage);

	void RenderUI();

	void Reset();
};

