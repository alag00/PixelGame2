#pragma once
#include "enemy.h"
#include <cmath>
#include "animation.h"


class FireBall
{
private:
	Entity* playerRef = nullptr;
	Vector2 pos{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };
	Vector2 size{ 0.f,0.f };
	float scale = 3.f;
	float speed = 10.f;
	Animator anim;
	bool lookLeft = true;
	float timeAlive = 0.f;
public:
	void SetRef(Entity& ref);
	void SetTxr(Texture2D txr);
	void Setup(Vector2 newPos, Vector2 newTarget, bool left);
	void Update(float dt);
	void Render();
	void Reset();

};

class PyromancerEnemy : public Enemy
{
private:
	Entity* playerRef = nullptr;
	Vector2 size{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };
	bool inFirstPhase = true;
	Animator anim;
	static const int p1TxrAmount = 10;
	Texture2D firstPhaseSprites[p1TxrAmount]{}; // 0 = Idle, Walk, Refill, Block, SuccessfulBlock, OilAttack, SeathAttack, SwordAttack1, SwordAttack2, Change Phase
	static const int p2TxrAmount = 11;
	Texture2D secondPhaseSprites[p2TxrAmount]{}; // 0 = Idle, Run, SuccessfulBlock, SwordAttack1, SwordAttack2, DeployWings, Fly,  Ranged attack, Flame projectiles, Fly attack, Death

	Sound sounds[3]{}; // 0 = Death, Init Attack, Attack

	DECISION dec = DECISION::IDLE;
	float scale = 3.f;
	float distance = 0.f;
	float p1Speed = 5.f;
	float p2Speed = 10.f;
	bool lookLeft = false;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };

	bool hasAdvantage = true;
	int switchAgroCounter = 2;

	int currentAttackId = 1;
	int lastAttackId = 0;

	Vector2 leftBorder{ 0.f,0.f };
	Vector2 rightBorder{ 0.f,0.f };

	float lDist = 0.f;
	float rDist = 0.f;

	int currentSlice = 1;
	float oilAmount = 1.f;

	int currentAttackNum = 0;
	const float attackCooldown = 0.5f;
	float attackTimer = attackCooldown;

	int attackStage = 0;

	FireBall fireBalls[3];
	float flyProgress = 0.f;

	bool push = false;

	float deadPause = 1.f;
public:
	~PyromancerEnemy();
	void SetTextures(Texture2D p1TxrList[], Texture2D p2TxrList[]);
	void SetAudio(Sound death, Sound init, Sound swing);
	void SetPlayerRef(Entity& ref) { playerRef = &ref; }
	void Setup();
	void Sense();
	void Decide();
	void Act(float dt);

	void Render();
	void CollisionCheck();

	void Move(float dt);

	void Attack(float dt);
	void OilAttack(float dt);
	void SeathAttack(float dt);
	void SliceAttack(float dt);
	void ThrustAttack(float dt);

	void FlameSlice(float dt);
	void FlameThrust(float dt);
	void FlameRangedAttack(float dt);
	void FlameFlyAttack(float dt);

	void AttackCollisionCheck();
	void EndAttack();

	void UpdateAgroSwitch();
	void Damaged(float dt);

	bool GetHit(Vector2 sourcePos, int potentialDamage, int id);

	void RenderUI();

	void Reset();

	void Phase1Decision();
	void Phase2Decision();
};