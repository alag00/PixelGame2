#pragma once
#include "animation.h"
#include <cmath>
#include <vector>
#include "entity.h"
#include "config.h"

enum class STATUS
{
	IDLE = 0,
	MOVING = 1,
	JUMPING = 2,
	FALLING = 3,
	DEFLECT = 4,
	ATTACK = 5,
	DAMAGED = 6,
	LOSTADVANTAGE = 7,
	AIRATTACK = 8,
	AIRRECOVERY = 9,
	AIRMOVEMENT = 10,
	CLIMB = 11,
	HOOK = 12,
};
class Player : public Entity
{
private:
	Config config;

	Texture2D idleAtlas = {};
	Texture2D walkAtlas = {};
	Texture2D fallAtlas = {};
	Texture2D jumpAtlas = {};
	Texture2D ledgeAtlas = {};
	Texture2D climbAtlas{};
	Texture2D climbSlideAtlas{};
	Texture2D hookAtlas{};

	Texture2D damagedAtlas = {};
	Texture2D deflectAtlas = {};
	Texture2D airDeflectAtlas = {};
	Texture2D successDeflectAtlas = {};
	Texture2D deflectParticleAtlas = {};

	Texture2D attackOneAtlas{};
	Texture2D attackTwoAtlas{};
	Texture2D airAttackAtlas{};

	Texture2D loseAdvantageAtlas{};
	Texture2D danceAtlas{};

	Animator anim;
	Animator particleAnim;

	
	Sound hitSound{};
	Sound deathSound{};
	Sound jumpSound{};
	Sound hookSound{};

	Vector2 size{0.f,0.f};
	Vector2 vel{ 0.f,0.f };
	float scale = 3.f;
	float speed = 10.f;
	float MAX_VELOCITY = 80.f;

	Rectangle attackBox{ 0.f,0.f,0.f,0.f };
	bool lookRight = true;
	
	bool onGround = false;
	float jumpTimer = 0.1f;
	float fallingTimer = 0.f;

	float defaultJumpPower = 20.f;
	float jumpCounter = 50.f;

	float ledgeJumpPower = 35.f;
	float currentJumpPower = 0.f;

	STATUS status = STATUS::IDLE;
	float deflectTimer = 0.f;

	Vector2 nextPos{ 0.f,0.f };

	int currentSlice = 1;
	float attackWindowTime = 0.5f;
	float attackWindowTimer = 0.f;

	bool playParticle = false;

	int currentAttackId = 1;
	int lastAttackId = 0;
	bool queuedAttack = false;
	bool queuedDeflect = false;

	Vector2 grappPoint = {0.f,0.f};
	bool inHookAnim = true;

	const float timeTillDance = 5.f;
	float danceTimer = 0.f;
	bool isDancing = false;

	Vector2 particlePos{ 0.f,0.f };
	const float pixelSize = 48.f;
	const float boxSize = 1.f;

	Color hookColor = { 241, 242, 224, 255 }; 

	const float downAccelation = 50.f;

	const float jumpForce = -14.f;
	const float recoilJumpForce = -7.f;
	const float movementSpeed = 10.f;

	const short int minPitch = 80;
	const short int maxPitch = 120;
	const float toRatio = 100.f;

	const float hookSpeed = 25.f;
	const float slideDownSpeed = 5.f;

	const float coyoteJumpTime = 0.1f;
	const float jumpBufferTime = 0.1f;
	const float hookOnHandOffset = 22.f;
	const float hookThickness = 5.f;

	const float gravity = 20.f;
	const float strongGravity = 35.f;

	const float endJumpBoost = -5.f;
	const int NEW_MAX_HEALTH = 100;

	const float DIVIDER = 2.f;
	const float ZERO = 0.f;

public:
	void Unload();
	Vector2 GetPosition() { return pos; }
	void SetPosition(float x, float y) { pos.x = x; pos.y = y; }
	Vector2 GetVelocity() { return vel; }
	void SetVelocity(float x, float y) { vel.x = x; vel.y = y; }

	Vector2 GetNextPos() { return nextPos; }

	void SetOnGround(bool newValue);
	void Setup();
	void Update(float dt);
	void Render();

	void Movement(float dt);
	void Control(float dt);



	void Jump();
	void RecoilJump();

	void Attack(float dt);
	void AirAttack(float dt);

	bool CollisionCheck(Entity& enemy);

	bool IsInAttackMode();
	void QueueAttackCheck();

	bool GetHit(Vector2 sourcePos, int potentialDamage, int id);

	

	void UpdateParticles();
	void RenderParticles();
	Vector2 GetCenter();
	void DamageRecovery(float dt);
	void InitAttack();
	void InitDeflect();
	void LoseAdvantage();

	void Die();
	void Respawn();

	void EnterClimbMode();
	void ClimbControl(float dt);

	void EnterGrapplingHookMode(Vector2 hookPos);
	void GrapplingHookMovement(float dt);
	bool GetLookSide() override { return lookRight; };
	void DanceCheck(float dt);

	void PlaySoundWithPitchDiff(Sound sound);
};
