#pragma once

#include "enemy.h"
#include "animation.h"
#include <cmath>


class GhostEnemy : public Enemy
{
private:
	Texture2D idleAtlas{};

	Entity* playerRef = nullptr;
	Animator anim;

	bool isHunting = false;
	const float HUNT_RADIUS = 5.f;

	float scale = 3.f;
	Vector2 size{ 0.f,0.f };

	bool lookRight = false;
	float distance = 0.f;

	DECISION dec = DECISION::IDLE;

	Rectangle hitBox{ 0.f,0.f,0.f,0.f };

	const short int ATTACK_DAMAGE = 10;
	const short int DEFLECTED_DAMAGE = 5;

	float attackCooldown = 1.f;
	float attackTimer = attackCooldown;

	float damagedTimer = 0.f;
	const Color NORMAL_COLOR{ 255, 255,255, 200 };
	const Color ATTACK_COLOR{ 255, 0, 0, 200 };

	const float SPEED = 2.f;

	const float WAIT_TIME = 2.f;
	float waitTimer = 0.f;
public:

	~GhostEnemy();
	void SetTextures(Texture2D idleTxr);
	void SetPlayerRef(Entity& ref) { playerRef = &ref; }
	void Setup();
	void Sense();
	void Decide();
	void Act(float dt);

	void Render();
	void CollisionCheck();

	void Move(float dt);

	void Reset();
	Vector2 GetCenter() override;
};
