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
	STATUS status = STATUS::IDLE;
	const int NEW_MAX_HEALTH = 100;
	const float DIVIDER = 2.f;
	const float ZERO = 0.f;
	const float DELTATIME_FAILSAFE = 0.1f;

	// VISUALITY VARIABLES
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

	Vector2 size{0.f,0.f};
	const float SCALE = 3.f;
	bool lookRight = true;
	const float SPRITE_SIZE_IN_PIXELS = 48.f;
	const float BOX_SIZE_IN_TILES = 1.f;
	const float OFFSET_TO_CENTER = 0.5f;
	const float OFFSET_PLAYER_Y = 40.f;
	const float ATTACK_BOX_WIDTH = 2.f;
	const float ATTACK_BOX_HEIGHT = 1.5f;
	
	// MOVEMENT VARIABLES
	const float MOVEMENT_SPEED = 10.f;
	const float GRAVITY = 20.f;
	const float GRAVITY_STRONG = 35.f;
	const float DOWNWARD_ACCELERATION = 50.f;
	Vector2 nextPos{ 0.f,0.f };
	Vector2 vel{ 0.f,0.f };
	const float SPEED = 10.f;
	const float MAX_VELOCITY = 80.f;
	const float KNOCKED_BACK_FORCE = 20.f;
	const float LOST_ADVANTAGE_SPEED = 2.f;
	const float FRICTION = 100.f;
	const float MIN_SPEED = 10.f;
	const float MIN_ATTACK_SPEED = 5.f;
	const float MAX_ATTACK_SPEED = 15.f;
	const float SLOW_AIR_MOVEMENT_SPEED = 2.5f;

	// ATTACK VARIABLES
	Rectangle attackBox{ 0.f,0.f,0.f,0.f };
	bool queuedAttack = false;
	const int PLAYER_DAMAGE = 10;
	int currentSlice = 1;
	const float ATTACK_WINDOW_TIME = 0.5f;
	float attackWindowTimer = 0.f;

	// DEFLECT VARIABLES
	bool queuedDeflect = false;
	float deflectTimer = 0.f;

	// JUMP VARIABLES
	const float JUMP_FORCE = -14.f;
	const float JUMP_FORCE_SMALL = -7.f;
	const float END_JUMP_BOOST = -5.f;
	const float KNOCKED_UP_FORCE= -5.f;
	const float JUMP_TIME_COYOTE = 0.1f;
	const float JUMP_TIME_BUFFERING = 0.1f;
	bool onGround = false;
	float jumpTimer = 0.1f;
	float fallingTimer = 0.f;


	// CLIMB VARIABLES
	const float SLIDE_DOWN_SPEED = 5.f;
	const float FORCE_TO_WALL = 10.f;
	const float WALL_JUMP_BOOST = -3.f;
	const float ANTI_CONTROL_TIME = 0.2f;
	float antiControlTimer = 0.f;

	// GRAPPLING HOOK VARIABLES
	const float GRAPPLING_SPEED = 25.f;
	const float GRAPPLING_OFFSET_TO_HAND = 22.f;
	const float GRAPPLING_LINE_THICKNESS = 5.f;
	const float GRAPPLING_END_DISTANCE_MARGIN = 1.f;
	const Color GRAPPLING_COLOR = { 241, 242, 224, 255 };
	Vector2 grapplingPoint = {0.f,0.f};
	bool inGrapplingAnim = true;


	// DANCE VARIABLES
	const float TIME_TILL_DANCE = 5.f;
	float danceTimer = 0.f;
	bool isDancing = false;

	// PARTICLE VARIABLES
	Vector2 particlePos{ 0.f,0.f };
	bool playParticle = false;

	// TICK DAMAGE
	const float TICK_TIME = 0.2f;
	float tickTimer = TICK_TIME;
	const int TICK_DAMAGE = 10;
		
	// AUDIO VARIABLES
	Sound hitSound{};
	Sound deathSound{};
	Sound jumpSound{};
	Sound hookSound{};
	const short int PITCH_MIN = 80;
	const short int PITCH_MAX = 120;
	const float PERCENT_TO_RATIO = 100.f;

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

	bool GetHit(Vector2 sourcePos, int potentialDamage);

	

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
	void FlipPlayer();

	void Damaged(Vector2 sourcePos, int damage);

	void ActivateParticles(Vector2 enemyPos);
	void EndAttack(Entity& enemy);
	void DeactivateAttackBox();

	void SlowAirControl(float dt);
	void TakeTickDamage();
};
