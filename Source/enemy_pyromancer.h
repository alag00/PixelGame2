#pragma once
#include "enemy.h"
#include <cmath>
#include "animation.h"
/*
enum PYROMANCER_AI
{
	IDLE, 
	MOVE,
	REFILL,
	ATTACK,
	BLOCK,

};
*/
class PyromancerEnemy : public Enemy
{
private:
	Entity* playerRef = nullptr;
	Vector2 size{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };
	bool inFirstPhase = true;
	Animator anim;
	static const int p1TxrAmount = 9;
	Texture2D firstPhaseSprites[p1TxrAmount]{}; // 0 = Idle, Walk, Refill, Block, SuccessfulBlock, OilAttack, SeathAttack, SwordAttack1, SwordAttack2
	static const int p2TxrAmount = 9;
	Texture2D secondPhaseSprites[p2TxrAmount]{}; // 0 = Idle, Run, SuccessfulBlock, Damaged, SwordAttack1, SwordAttack2, Ranged attack, Flame projectiles, Fly attack
	//Texture2D idleAtlas{};
	//Texture2D walkAtlas{};
	//Texture2D refillAtlas{};
	//Texture2D attackOneAtlas{};
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
	Vector2 rightBorder{ 0.f,0.f };

	float lDist = 0.f;
	float rDist = 0.f;

	int currentSlice = 1;
	float oilAmount = 1.f;
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

	void Walk(float dt);
	void Attack(float dt);

	void UpdateAgroSwitch();

	bool GetHit(Vector2 sourcePos, int potentialDamage, int id);

	void RenderUI();

	void Reset();

	void Phase1Decision();
	void Phase2Decision();
};