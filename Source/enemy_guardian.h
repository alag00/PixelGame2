#pragma once

#include "enemy.h"
#include <cmath>
#include "animation.h"


class GuardianEnemy : public Enemy
{
	Entity* playerRef = nullptr;
	Vector2 size{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };

	Animator anim;
	Texture2D textures[6]; // 0 = IDLE, WALK, Slice, Grab Init , Grab Hit, DEATH


	Sound deathSound{};
	Sound initAttackSound{};
	Sound swingAttackSound{};

	DECISION dec = DECISION::IDLE;
	float scale = 3.f;
	float distance = 0.f;
	float speed = 4.f;
	const float DASH_SPEED = 20.f;
	bool lookRight = true;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };



	const short int ATTACK_DAMAGE = 10;
	const short int DEFLECTED_DAMAGE = 5;

	Vector2 leftBorder{ 0.f,0.f };
	Vector2 rightBorder{ 0.f,0.f };

	float lDist = 0.f;
	float rDist = 0.f;

	int currentSlice = 1;

	const float HURT_TIME = 0.1f;
	float hurtTimer = 0.f;

	const float PAUSE_TIME = 1.f;
	float pauseTimer = PAUSE_TIME;
	bool grabbing = false;

	float grabProgress = 0.f;
	const float SLOW_FRAME_RATE = 6.f;
	const float FAST_FRAME_RATE = 12.f;

	const float ATTACK_COOLDOWN_TIME = 1.f;
	float cooldownTimer = ATTACK_COOLDOWN_TIME;
public:
	~GuardianEnemy();
	void SetTextures(Texture2D txr[]);
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
	void GrabDash(float dt);
	void GrabHit(float dt);
	bool GetHit(Vector2 sourcePos, int potentialDamage);

	void RenderUI();

	void Reset();
};