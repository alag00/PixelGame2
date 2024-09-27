#include "player.h"

void Player::Unload()
{
	
	UnloadTexture(idleAtlas);
	UnloadTexture(walkAtlas);
	UnloadTexture(fallAtlas);
	UnloadTexture(jumpAtlas);
	UnloadTexture(ledgeAtlas);
	UnloadTexture(climbAtlas);
	UnloadTexture(climbSlideAtlas);
	UnloadTexture(hookAtlas);

	UnloadTexture(airAttackAtlas);
	UnloadTexture(attackOneAtlas);
	UnloadTexture(attackTwoAtlas);
	UnloadTexture(deflectAtlas);
	UnloadTexture(airDeflectAtlas);
	UnloadTexture(successDeflectAtlas);
	UnloadTexture(damagedAtlas);
	UnloadTexture(loseAdvantageAtlas);

	UnloadTexture(deflectParticleAtlas);

	
	UnloadSound(hitSound);
	UnloadSound(deathSound);
	UnloadSound(jumpSound);
	UnloadSound(hookSound);
}

void Player::Setup()
{
	idleAtlas = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	walkAtlas = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	fallAtlas = LoadTexture("Assets/PlayerTextures/FallAtlas.png");
	jumpAtlas = LoadTexture("Assets/PlayerTextures/JumpAtlas.png");
	ledgeAtlas = LoadTexture("Assets/PlayerTextures/LedgeClimbAtlasAlter.png");
	climbAtlas = LoadTexture("Assets/PlayerTextures/ClimbAtlas.png");
	climbSlideAtlas = LoadTexture("Assets/PlayerTextures/ClimbSlideAtlas.png");
	hookAtlas = LoadTexture("Assets/PlayerTextures/GrapplingHookAtlas.png");

	airAttackAtlas = LoadTexture("Assets/PlayerTextures/AirAttackAtlas.png");
	attackOneAtlas = LoadTexture("Assets/PlayerTextures/FirstSliceAtlasAlter.png");
	attackTwoAtlas = LoadTexture("Assets/PlayerTextures/SecondSliceAtlas.png");
	deflectAtlas = LoadTexture("Assets/PlayerTextures/DeflectAtlas.png");
	airDeflectAtlas = LoadTexture("Assets/PlayerTextures/AirDeflectAtlas.png");
	successDeflectAtlas = LoadTexture("Assets/PlayerTextures/SuccessfulDeflectAtlas.png");
	damagedAtlas = LoadTexture("Assets/PlayerTextures/DamagedAtlas.png");
	loseAdvantageAtlas = LoadTexture("Assets/PlayerTextures/AdvantageLostAtlas.png");
	danceAtlas = LoadTexture("Assets/PlayerTextures/DanceAtlas.png");

	deflectParticleAtlas = LoadTexture("Assets/Particles/DeflectParticleAtlasAlter.png");

	hitSound = LoadSound("Assets/Audio/SFX/Hit.mp3");
	deathSound = LoadSound("Assets/Audio/SFX/PlayerDeath.mp3");
	jumpSound = LoadSound("Assets/Audio/SFX/Jump.mp3");
	hookSound = LoadSound("Assets/Audio/SFX/Hook.mp3");

	anim.SetAnimation(idleAtlas, 8, true);
	particleAnim.SetAnimation(deflectParticleAtlas, 5, true);

	size.x = SPRITE_SIZE_IN_PIXELS * config.pixelScale;
	size.y = SPRITE_SIZE_IN_PIXELS * config.pixelScale;

	maxHealth = NEW_MAX_HEALTH;
	health = maxHealth;
}

void Player::Update(float dt)
{
	UpdateParticles();
	anim.UpdateAnimator(dt);
	particleAnim.UpdateAnimator(dt);
	DanceCheck(dt);
	tickTimer -= dt;
	hitBox = { pos.x, pos.y, BOX_SIZE_IN_TILES, BOX_SIZE_IN_TILES };
	switch (status)
	{
	case STATUS::ATTACK: 
		Attack(dt);
		break;
	case STATUS::AIRATTACK:
		AirAttack(dt);
		break;
	case STATUS::DAMAGED:
		DamageRecovery(dt);
		break;
	case STATUS::LOSTADVANTAGE:
		vel.y += GRAVITY * dt;
		QueueAttackCheck();
		if (queuedDeflect)
		{
			InitDeflect();
		}
		if (anim.GetCurrentFrame() >= 6)
		{
			status = STATUS::IDLE;
			
			if (queuedAttack)
			{
				InitAttack();
			}
		}
		break;
	case STATUS::CLIMB:
		ClimbControl(dt);
		break;
	case STATUS::HOOK:
		GrapplingHookMovement(dt);
		break;
		
	case STATUS::AIRRECOVERY:
		SlowAirControl(dt);
		break;
	case STATUS::AIRMOVEMENT:
		antiControlTimer -= dt;
		if (antiControlTimer < 0.f)
		{
			Control(dt);
		}
		Movement(dt);
		break;
	default:
		Control(dt);
		Movement(dt);
		break;
	}
	
}

void Player::Render()
{
	Rectangle dst = { pos.x, pos.y, size.x, size.y };
	dst = { pos.x * config.tileSize + config.tileSize / DIVIDER, pos.y * config.tileSize + OFFSET_PLAYER_Y, size.x, size.y };
	Vector2 origin = { dst.width / DIVIDER, dst.height / DIVIDER };
	anim.DrawAnimationPro(dst, origin, ZERO, WHITE);




	RenderParticles();

	if (status == STATUS::HOOK)
	{
	
		Vector2 vec1 = { GetCenter().x * config.tileSize, GetCenter().y * config.tileSize };
		vec1.x += (lookRight) ? GRAPPLING_OFFSET_TO_HAND : -GRAPPLING_OFFSET_TO_HAND;
		Vector2 vec2 = { grapplingPoint.x * config.tileSize, grapplingPoint.y * config.tileSize };

		DrawLineBezier(vec1, vec2, GRAPPLING_LINE_THICKNESS, GRAPPLING_COLOR);
	}
}

void Player::Movement(float dt)
{	
	
	if (vel.y > ZERO && status != STATUS::FALLING && status != STATUS::DEFLECT && status != STATUS::AIRRECOVERY && status != STATUS::AIRMOVEMENT)
	{
		anim.SetAnimation(fallAtlas, 4, true);
		status = STATUS::FALLING;
	}
	if (dt < DELTATIME_FAILSAFE)
	{
		vel.y += (status != STATUS::FALLING) ? GRAVITY * dt : GRAVITY_STRONG * dt;
	}
	

	jumpTimer += dt;
	fallingTimer += dt;

}

void Player::Control(float dt)
{


	if (status == STATUS::AIRMOVEMENT && !onGround || status == STATUS::DEFLECT && !onGround)
	{

	}
	else
	{

		if (vel.x != ZERO)
		{
			vel.x = (vel.x > ZERO) ? vel.x - dt * FRICTION : vel.x + dt * FRICTION;
		}


		if (fabs(vel.x) <= MIN_SPEED)
		{
			vel.x = ZERO;
		}
	}
	
	if (status == STATUS::DEFLECT)
	{
		QueueAttackCheck();
		if (anim.GetCurrentFrame() < 4)
		{
			return;
		}
		if (queuedAttack)
		{
			InitAttack();
			return;
		}
		if (queuedDeflect)
		{
			anim.SetAnimation(idleAtlas, 8, true);
			InitDeflect();
			return;
		}
		if (onGround)
		{

			anim.SetAnimation(idleAtlas, 8, true);
			status = STATUS::IDLE;
		}
		else
		{
			anim.SetAnimation(fallAtlas, 4, true);
			status = STATUS::FALLING;
		}
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		if (onGround)
		{

			Jump();
		}
		else {

			if (fallingTimer > ZERO && fallingTimer < JUMP_TIME_COYOTE)
			{
				Jump();
			}

			jumpTimer = ZERO;
		}
	}
	if (IsKeyReleased(KEY_SPACE) && status == STATUS::JUMPING)
	{
		vel.y = (vel.y < END_JUMP_BOOST) ? END_JUMP_BOOST : vel.y;
	}
	if (IsKeyDown(KEY_A))
	{
		vel.x = -MOVEMENT_SPEED;
		if (status == STATUS::IDLE && onGround)
		{
			status = STATUS::MOVING;
			anim.SetAnimation(walkAtlas, 8, true);
		}
		if (lookRight)
		{
			FlipPlayer();
		}
	}
	if (IsKeyDown(KEY_D))
	{
		vel.x = MOVEMENT_SPEED;
		if (status == STATUS::IDLE && onGround)
		{
			status = STATUS::MOVING;
			anim.SetAnimation(walkAtlas, 8, true);
		}
		if (!lookRight)
		{
			FlipPlayer();
		}
	}
	if (status != STATUS::IDLE && onGround && !IsKeyDown(KEY_D) && !IsKeyDown(KEY_A))
	{
		anim.SetAnimation(idleAtlas, 8, true);
		status = STATUS::IDLE;
	}
	if (IsKeyPressed(KEY_O))
	{
		InitAttack();
	
	}
	if (IsKeyPressed(KEY_P))
	{
		InitDeflect();
	}

	if (IsKeyDown(KEY_S))
	{
		if (status == STATUS::FALLING || status == STATUS::JUMPING)
		{
			vel.y += dt * DOWNWARD_ACCELERATION;
		}
	}
}

void Player::RecoilJump()
{
	status = STATUS::AIRMOVEMENT;
	anim.SetAnimation(jumpAtlas, 8, true);
	vel.y = JUMP_FORCE_SMALL;
	vel.x = (lookRight) ? MOVEMENT_SPEED : -MOVEMENT_SPEED;

}

void Player::Jump()
{
	anim.SetAnimation(jumpAtlas, 8, true);
	onGround = false;
	status = STATUS::JUMPING;
	vel.y = JUMP_FORCE;

	PlaySoundWithPitchDiff(jumpSound);
}

void Player::SetOnGround(bool newValue)
{
	onGround = newValue;
	
	if (onGround)
	{
		fallingTimer = ZERO;
		if (jumpTimer > ZERO && jumpTimer <= JUMP_TIME_BUFFERING)
		{
			Jump();
		}
		
		else if (status == STATUS::FALLING || status == STATUS::AIRRECOVERY || status == STATUS::AIRATTACK || status == STATUS::AIRMOVEMENT || status == STATUS::DAMAGED)
		{
			vel.y = ZERO;
			status = STATUS::IDLE;

			anim.SetAnimation(idleAtlas, 8, true);
		}

	}
}

void Player::Attack(float dt)
{
	vel.y += GRAVITY * dt;
	QueueAttackCheck();
	attackBox = { pos.x, pos.y - OFFSET_TO_CENTER , ATTACK_BOX_WIDTH, ATTACK_BOX_HEIGHT };
	attackBox.x = (!lookRight) ? pos.x - BOX_SIZE_IN_TILES : pos.x;

	switch (anim.GetCurrentFrame())
	{
	case 0:
		vel.x = (lookRight) ? MIN_ATTACK_SPEED : -MIN_ATTACK_SPEED;
		break;
	case 1:
		vel.x = (lookRight) ? MAX_ATTACK_SPEED : -MAX_ATTACK_SPEED;
		break;
	case 2:
		vel.x = (lookRight) ? MAX_ATTACK_SPEED : -MAX_ATTACK_SPEED;
		break;
	case 3:
		vel.x = (lookRight) ? MIN_ATTACK_SPEED : -MIN_ATTACK_SPEED;
		break;
	case 4:
	
		break;
	case 5:
	
		break;
	case 6:
		vel.x = ZERO;
		status = STATUS::IDLE;
	
		DeactivateAttackBox();

		if (queuedDeflect)
		{
			InitDeflect();
		}
		else if (queuedAttack)
		{
			InitAttack();
		}

		break;
	}
	
	
}

void Player::AirAttack(float dt)
{
	vel.y += GRAVITY * dt;
	attackBox = { pos.x, pos.y, BOX_SIZE_IN_TILES, BOX_SIZE_IN_TILES };
	attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);

	if (vel.x == ZERO)
	{
		FlipPlayer();

		status = STATUS::AIRRECOVERY;
		anim.SetAnimation(jumpAtlas, 8, true);
		vel.y = JUMP_FORCE_SMALL;
		vel.x = (lookRight) ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
	
		DeactivateAttackBox();
		PlaySoundWithPitchDiff(hitSound);
	}
}

bool Player::CollisionCheck(Entity& enemy)
{
	if (status != STATUS::ATTACK && status != STATUS::AIRATTACK)
	{
		return false;
	}
	if (CheckCollisionRecs(attackBox, enemy.hitBox))
	{
		switch (status)
		{
		case  STATUS::ATTACK:
			if (anim.GetCurrentFrame() >= 2)
			{
				status = STATUS::IDLE;
				ActivateParticles(enemy.pos);
				EndAttack(enemy);
				vel.x = (lookRight) ? -KNOCKED_BACK_FORCE : KNOCKED_BACK_FORCE;
				LoseAdvantage();

				return true;
			}
			break;

		case  STATUS::AIRATTACK:

			status = STATUS::AIRRECOVERY;
			ActivateParticles(enemy.pos);
			EndAttack(enemy);
			anim.SetAnimation(jumpAtlas, 8, true);
			vel.y = JUMP_FORCE_SMALL;
			vel.x = (lookRight) ? MOVEMENT_SPEED : -MOVEMENT_SPEED;

			return true;
			break;
		}
	}

	return false;
}

bool Player::IsInAttackMode()
{
	if (status != STATUS::ATTACK && status != STATUS::AIRATTACK)
	{
		return false;
	}
	return true;
}

void Player::QueueAttackCheck()
{
	if (IsKeyPressed(KEY_P))
	{
		queuedDeflect = true;
		queuedAttack = false;
	}
	else if (IsKeyPressed(KEY_O))
	{
		queuedAttack = true;
		queuedDeflect = false;
	}
	else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		queuedAttack = false;
		queuedDeflect = false;
	}
}

bool Player::GetHit(Vector2 sourcePos, int potentialDamage)
{
	if (status == STATUS::DAMAGED)
	{
		return true;
	}

	PlaySoundWithPitchDiff(hitSound);

	if (status == STATUS::DEFLECT && anim.GetCurrentFrame() >= 2)
	{

		anim.SetAnimation(successDeflectAtlas, 5, false);
		vel.x = (sourcePos.x > pos.x) ? -KNOCKED_BACK_FORCE : KNOCKED_BACK_FORCE;

		ActivateParticles(sourcePos);
	}
	else
	{
		Damaged(sourcePos, potentialDamage);
		return true;
	}


	return false;
}

void Player::UpdateParticles()
{
	if (!playParticle)
	{
		return;
	}
	if (particleAnim.GetCurrentFrame() == 4)
	{
		playParticle = false;
	}
}

void Player::RenderParticles()
{
	if (!playParticle)
	{
		return;
	}
	Rectangle dst = { particlePos.x * config.tileSize, particlePos.y * config.tileSize, size.x, size.y };
	
	Vector2 origin = { dst.width / DIVIDER, dst.height / DIVIDER };

	
	particleAnim.DrawAnimationPro(dst, origin, ZERO, WHITE);

}

Vector2 Player::GetCenter()
{
	return Vector2(pos.x + OFFSET_TO_CENTER, pos.y + OFFSET_TO_CENTER);
}

void Player::DamageRecovery(float dt)
{
	vel.y += GRAVITY * dt;

	jumpTimer += dt;
	fallingTimer += dt;

	if (anim.GetCurrentFrame() >= 7)
	{
		status = STATUS::IDLE;
	}
}

void Player::InitAttack()
{
	if (onGround)
	{
		
		vel.x = ZERO;
		vel.y = ZERO;
		status = STATUS::ATTACK;
		queuedAttack = false;
		switch (currentSlice)
		{
		case 1:
			anim.SetAnimation(attackTwoAtlas, 7, false);
			currentSlice = 2;
			break;
		case 2:
			anim.SetAnimation(attackOneAtlas, 7, false);
			currentSlice = 1;
			break;
		}
		attackBox = { pos.x, pos.y - OFFSET_TO_CENTER , ATTACK_BOX_WIDTH, ATTACK_BOX_HEIGHT};
		attackBox.x = (!lookRight) ? pos.x - BOX_SIZE_IN_TILES : pos.x;
	}
	else
	{
		anim.SetAnimation(airAttackAtlas, 4, true);
		status = STATUS::AIRATTACK;
		vel.x = (lookRight) ? MOVEMENT_SPEED : -MOVEMENT_SPEED;
		vel.y = END_JUMP_BOOST;

		PlaySoundWithPitchDiff(jumpSound);

		attackBox = { pos.x, pos.y, BOX_SIZE_IN_TILES, BOX_SIZE_IN_TILES };
		attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);
	
	}

}

void Player::InitDeflect()
{
	if (onGround)
	{
		anim.SetAnimation(deflectAtlas, 5, true);
	}
	else
	{
		anim.SetAnimation(airDeflectAtlas, 5, true);
	}
	status = STATUS::DEFLECT;
	queuedDeflect = false;
}

void Player::LoseAdvantage()
{
	if (status == STATUS::AIRRECOVERY)
	{
		return;
	}
	anim.SetAnimation(loseAdvantageAtlas, 7, false);
	status = STATUS::LOSTADVANTAGE;
	vel.x = (lookRight) ? -LOST_ADVANTAGE_SPEED : LOST_ADVANTAGE_SPEED;
}

void  Player::Die()
{
	PlaySound(deathSound);
}

void Player::Respawn()
{
	status = STATUS::IDLE;
	anim.SetAnimation(idleAtlas, 8, true);
	health = maxHealth;
	vel = { ZERO,ZERO };
}

void Player::EnterClimbMode()
{
	status = STATUS::CLIMB;
}

void Player::ClimbControl(float dt)
{
	vel = { ZERO,ZERO };
	vel.x += (lookRight) ? FORCE_TO_WALL *dt : -FORCE_TO_WALL *dt;
	if (IsKeyPressed(KEY_SPACE))
	{
		FlipPlayer();

		RecoilJump();
		antiControlTimer = ANTI_CONTROL_TIME;
		vel.y += WALL_JUMP_BOOST;
		return;
	}
	else if (IsKeyDown(KEY_S))
	{
		vel.y = SLIDE_DOWN_SPEED;
		anim.SetAnimation(climbSlideAtlas, 4, true);
		if (IsKeyDown(KEY_A) && lookRight || IsKeyDown(KEY_D) && !lookRight)
		{
			FlipPlayer();
			status = STATUS::FALLING;
			anim.SetAnimation(fallAtlas, 4, true);
		}
	}
	else
	{
		anim.SetAnimation(climbAtlas, 8, true);
	}
	status = STATUS::FALLING;

	
}

void Player::EnterGrapplingHookMode(Vector2 hookPos)
{
	if (status == STATUS::HOOK)
	{
		return;
	}
	inGrapplingAnim = true;
	grapplingPoint.x = hookPos.x;
	grapplingPoint.y = hookPos.y;
	status = STATUS::HOOK;
	anim.SetAnimation(hookAtlas, 5, false);

	vel = { ZERO,ZERO };

	PlaySoundWithPitchDiff(hookSound);
}

void Player::GrapplingHookMovement(float dt)
{
	if (inGrapplingAnim)
	{
		if (anim.GetCurrentFrame() >= 4)
		{
			inGrapplingAnim = false;
			anim.SetAnimation(jumpAtlas, 8, true);
			
		}
	}
	float x = grapplingPoint.x - GetCenter().x;
	float y = grapplingPoint.y - GetCenter().y;
	float mag = sqrtf(x * x + y * y);
	x /= mag;
	y /= mag;

	

	vel.x += x * dt * GRAPPLING_SPEED;
	vel.y += y * dt * GRAPPLING_SPEED;

	if (mag < GRAPPLING_END_DISTANCE_MARGIN || IsKeyPressed(KEY_SPACE))
	{
		RecoilJump();
	}

}

void Player::DanceCheck(float dt)
{
	if (status != STATUS::IDLE)
	{
		danceTimer = ZERO;
		isDancing = false;
		return;
	}
	danceTimer += dt;
	if (danceTimer > TIME_TILL_DANCE && !isDancing)
	{
		isDancing = true;
		anim.SetAnimation(danceAtlas, 8, true);
	}
}

void Player::PlaySoundWithPitchDiff(Sound sound)
{
	float randNum = (float)GetRandomValue(PITCH_MIN, PITCH_MAX);
	randNum /= PERCENT_TO_RATIO;
	SetSoundPitch(sound, randNum);
	PlaySound(sound);
}

void Player::FlipPlayer()
{
	lookRight = !lookRight;
	anim.FlipAnimationHorizontal();
	particleAnim.FlipAnimationHorizontal();
}

void Player::Damaged(Vector2 sourcePos, int damage)
{
	health -= damage;
	vel.x = (sourcePos.x > pos.x) ? -MOVEMENT_SPEED : MOVEMENT_SPEED;
	vel.y = KNOCKED_UP_FORCE;
	status = STATUS::DAMAGED;
	anim.SetAnimation(damagedAtlas, 8, false);
	if (!lookRight && vel.x < ZERO || lookRight && vel.x > ZERO)
	{
		FlipPlayer();
	}
}

void Player::ActivateParticles(Vector2 enemyPos)
{
	particleAnim.RestartAnimation();
	playParticle = true;
	float xOffset = (GetCenter().x - enemyPos.x) / DIVIDER;
	float yOffset = (GetCenter().y - enemyPos.y) / DIVIDER;
	particlePos = { GetCenter().x - xOffset, GetCenter().y - yOffset };
}

void Player::EndAttack(Entity& enemy)
{
	enemy.GetHit(pos, PLAYER_DAMAGE);
	DeactivateAttackBox();
	PlaySoundWithPitchDiff(hitSound);
}

void Player::DeactivateAttackBox()
{
	attackBox.width = ZERO;
	attackBox.height = ZERO;
}

void Player::SlowAirControl(float dt)
{
	vel.y += GRAVITY_STRONG * dt;
	

	if (IsKeyDown(KEY_A))
	{
		vel.x = (lookRight) ?  MOVEMENT_SPEED - SLOW_AIR_MOVEMENT_SPEED : -MOVEMENT_SPEED - (SLOW_AIR_MOVEMENT_SPEED / 2.f);
	}
	if (IsKeyDown(KEY_D))
	{
		vel.x = (lookRight) ? MOVEMENT_SPEED + (SLOW_AIR_MOVEMENT_SPEED / 2.f)  : -MOVEMENT_SPEED + SLOW_AIR_MOVEMENT_SPEED;
	}
	if (onGround)
	{
		status = STATUS::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
	}
}

void Player::TakeTickDamage()
{
	if (tickTimer <= 0.f)
	{
		tickTimer = TICK_TIME;
		health -= TICK_DAMAGE;
	}
}
