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

	size.x = pixelSize * config.pixelScale;
	size.y = pixelSize * config.pixelScale;

	

	maxHealth = NEW_MAX_HEALTH;
	health = maxHealth;
}

void Player::Update(float dt)
{
	UpdateParticles();
	anim.UpdateAnimator(dt);
	particleAnim.UpdateAnimator(dt);
	DanceCheck(dt);
	hitBox = { pos.x, pos.y, boxSize, boxSize };
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
		vel.y += gravity * dt;
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
		vel.y += strongGravity * dt;
		if (onGround)
		{
			status = STATUS::IDLE;
			anim.SetAnimation(idleAtlas, 8, true);
		}
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
	dst = { pos.x * config.tileSize + config.tileSize / DIVIDER, pos.y * config.tileSize + 40.f, size.x, size.y };
	Vector2 origin = { dst.width / DIVIDER, dst.height / DIVIDER };
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);




	RenderParticles();

	if (status == STATUS::HOOK)
	{
	
		Vector2 vec1 = { GetCenter().x * config.tileSize, GetCenter().y * config.tileSize };
		vec1.x += (lookRight) ? hookOnHandOffset : -hookOnHandOffset;
		Vector2 vec2 = { grappPoint.x * config.tileSize, grappPoint.y * config.tileSize };

		DrawLineBezier(vec1, vec2, hookThickness, hookColor);
	}
}

void Player::Movement(float dt)
{	
	
	if (vel.y > 0.f && status != STATUS::FALLING && status != STATUS::DEFLECT && status != STATUS::AIRRECOVERY && status != STATUS::AIRMOVEMENT)
	{
		anim.SetAnimation(fallAtlas, 4, true);
		status = STATUS::FALLING;
	}
	if (dt < 0.1f)
	{
		vel.y += (status != STATUS::FALLING) ? gravity * dt : strongGravity * dt;
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

		if (vel.x != 0.f)
		{
			vel.x = (vel.x > 0.f) ? vel.x - dt * 100.f : vel.x + dt * 100.f;
		}


		if (fabs(vel.x) <= 10.0f)
		{
			vel.x = 0.f;
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

			if (fallingTimer > ZERO && fallingTimer < coyoteJumpTime)
			{
				Jump();
			}

			jumpTimer = ZERO;
		}
	}
	if (IsKeyReleased(KEY_SPACE) && status == STATUS::JUMPING)
	{
		vel.y = (vel.y < endJumpBoost) ? endJumpBoost : vel.y;
	}
	if (IsKeyDown(KEY_A))
	{
		vel.x = -movementSpeed;
		if (status == STATUS::IDLE && onGround)
		{
			status = STATUS::MOVING;
			anim.SetAnimation(walkAtlas, 8, true);
		}
		if (lookRight)
		{
			anim.FlipAnimationHorizontal();
			particleAnim.FlipAnimationHorizontal();
			lookRight = !lookRight;
		}
	}
	if (IsKeyDown(KEY_D))
	{
		vel.x = movementSpeed;
		if (status == STATUS::IDLE && onGround)
		{
			status = STATUS::MOVING;
			anim.SetAnimation(walkAtlas, 8, true);
		}
		if (!lookRight)
		{
			anim.FlipAnimationHorizontal();
			particleAnim.FlipAnimationHorizontal();
			lookRight = !lookRight;
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
			vel.y += dt * downAccelation;
		}
	}
}

void Player::RecoilJump()
{
	status = STATUS::AIRMOVEMENT;
	anim.SetAnimation(jumpAtlas, 8, true);
	vel.y = recoilJumpForce;
	vel.x = (lookRight) ? movementSpeed : -movementSpeed;

}

void Player::Jump()
{
	anim.SetAnimation(jumpAtlas, 8, true);
	onGround = false;
	status = STATUS::JUMPING;
	vel.y = jumpForce;

	PlaySoundWithPitchDiff(jumpSound);
}
void Player::SetOnGround(bool newValue)
{
	onGround = newValue;
	
	if (onGround)
	{
		jumpCounter = ZERO;
		fallingTimer = ZERO;
		if (jumpTimer > ZERO && jumpTimer <= jumpBufferTime)
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
	vel.y += 20.f * dt;
	QueueAttackCheck();
	attackBox = { pos.x, pos.y - 0.5f , 2.f, 1.5 };
	attackBox.x = (!lookRight) ? pos.x -1.f : pos.x;

	switch (anim.GetCurrentFrame())
	{
	case 0:
		vel.x = (lookRight) ? 5.f : -5.f;
		break;
	case 1:
		vel.x = (lookRight) ? 15.f : -15.f;
		break;
	case 2:
		vel.x = (lookRight) ? 15.f : -15.f;
		break;
	case 3:
		vel.x = (lookRight) ? 5.f : -5.f;
		break;
	case 4:
	
		break;
	case 5:
	
		break;
	case 6:
		vel.x = 0.f;
		status = STATUS::IDLE;
	
		attackBox.width = 0.f;
		attackBox.height = 0.f;

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
	vel.y += 20.f * dt;
	attackBox = { pos.x, pos.y, 1, 1 };
	attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);

	if (vel.x == 0.f)
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
		particleAnim.FlipAnimationHorizontal();

		status = STATUS::AIRRECOVERY;
		anim.SetAnimation(jumpAtlas, 8, true);
		vel.y = -7.f;
		vel.x = (lookRight) ? 10.f : -10.f;
	

		attackBox.width = 0.f;
		attackBox.height = 0.f;


		PlaySoundWithPitchDiff(hitSound);
	}
}

bool Player::CollisionCheck(Entity& enemy)
{
	if (status != STATUS::ATTACK && status != STATUS::AIRATTACK)
	{
		return false;
	}
	switch (status)
	{
	case  STATUS::ATTACK:
		if (anim.GetCurrentFrame() >= 2)
		{

			if (CheckCollisionRecs(attackBox, enemy.hitBox))
			{
				status = STATUS::IDLE;

				particleAnim.RestartAnimation();
				playParticle = true;
				float xOffset = (GetCenter().x - enemy.pos.x) / 2.f;
				float yOffset = (GetCenter().y - enemy.pos.y) / 2.f;
				particlePos = { GetCenter().x - xOffset, GetCenter().y - yOffset };

				vel.x = (lookRight) ? -20.f : 20.f;

				enemy.GetHit(pos, 10, currentAttackId);

				attackBox.width = 0.f;
				attackBox.height = 0.f;

				PlaySoundWithPitchDiff(hitSound);

				LoseAdvantage();
			
				return true;
			}

		}
		break;
	case  STATUS::AIRATTACK:
		if (CheckCollisionRecs(attackBox, enemy.hitBox))
		{
			
			particleAnim.RestartAnimation();
			playParticle = true;
			float xOffset = (GetCenter().x - enemy.pos.x) / 2.f;
			float yOffset = (GetCenter().y - enemy.pos.y) / 2.f;
			particlePos = { GetCenter().x - xOffset, GetCenter().y - yOffset };

			enemy.GetHit(pos, 10, currentAttackId);

			status = STATUS::AIRRECOVERY;
			anim.SetAnimation(jumpAtlas, 8, true);
			vel.y = -7.f;
			vel.x = (lookRight) ? 10.f : -10.f;
		




			attackBox.width = 0.f;
			attackBox.height = 0.f;

			PlaySoundWithPitchDiff(hitSound);
			return true;
		}
		break;
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

bool Player::GetHit(Vector2 sourcePos, int potentialDamage, int id)
{
	if (status == STATUS::DAMAGED)
	{
		return true;
	}
	(void)id;

	PlaySoundWithPitchDiff(hitSound);

	if (status != STATUS::DEFLECT)
	{
		health -= potentialDamage;
		vel.x = (sourcePos.x > pos.x) ? -10.f : 10.f;
		vel.y = -5.f;
		status = STATUS::DAMAGED;
		anim.SetAnimation(damagedAtlas, 8, false);
		if (!lookRight && vel.x < 0.f || lookRight && vel.x > 0.f)
		{
			anim.FlipAnimationHorizontal();
			lookRight = !lookRight;
		}
		return true;
	}
	anim.SetAnimation(successDeflectAtlas, 5, false);
	vel.x = (sourcePos.x > pos.x) ? -20.f : 20.f;

	particleAnim.RestartAnimation();
	playParticle = true;
	float xOffset = (GetCenter().x - sourcePos.x) / 2.f;
	float yOffset = (GetCenter().y - sourcePos.y) / 2.f;
	particlePos = { GetCenter().x - xOffset, GetCenter().y - yOffset };


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
	Rectangle dst = { particlePos.x * 64.f, particlePos.y * 64.f, size.x, size.y };
	
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };

	
	particleAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

}

Vector2 Player::GetCenter()
{
	return Vector2(pos.x + 0.5f, pos.y + 0.5f);
}

void Player::DamageRecovery(float dt)
{
	vel.y += 20.f * dt;

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
		
		vel.x = 0.f;
		vel.y = 0.f;
		status = STATUS::ATTACK;
		currentAttackId++;
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
		attackBox = { pos.x, pos.y - 0.5f , 2.f, 1.5 };
		attackBox.x = (!lookRight) ? pos.x - 1.f : pos.x;
	}
	else
	{
		anim.SetAnimation(airAttackAtlas, 4, true);
		status = STATUS::AIRATTACK;
		vel.x = (lookRight) ? 10.f : -10.f;
		vel.y = -5.f;

		PlaySoundWithPitchDiff(jumpSound);

		attackBox = { pos.x, pos.y, boxSize, boxSize };
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
	anim.SetAnimation(loseAdvantageAtlas, 7, false);
	status = STATUS::LOSTADVANTAGE;
	vel.x = (lookRight) ? -2.f : 2.f ;
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
	vel = { 0.f,0.f };
}


void Player::EnterClimbMode()
{
	status = STATUS::CLIMB;
}
void Player::ClimbControl(float dt)
{
	dt;
	vel = { 0.f,0.f };
	vel.x += (lookRight) ? 10.f*dt : -10.f*dt;
	if (IsKeyPressed(KEY_SPACE))
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
		particleAnim.FlipAnimationHorizontal();
		RecoilJump();
		vel.y += -3.f;
		return;
	}
	else if (IsKeyDown(KEY_S))
	{
		vel.y = slideDownSpeed;
		anim.SetAnimation(climbSlideAtlas, 4, true);
		if (IsKeyDown(KEY_A) && lookRight || IsKeyDown(KEY_D) && !lookRight)
		{
			lookRight = !lookRight;
			anim.FlipAnimationHorizontal();
			particleAnim.FlipAnimationHorizontal();
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
	inHookAnim = true;
	grappPoint.x = hookPos.x;
	grappPoint.y = hookPos.y;
	status = STATUS::HOOK;
	anim.SetAnimation(hookAtlas, 5, false);

	vel = { 0.f,0.f };

	PlaySoundWithPitchDiff(hookSound);
}

void Player::GrapplingHookMovement(float dt)
{
	if (inHookAnim)
	{
		if (anim.GetCurrentFrame() >= 4)
		{
			inHookAnim = false;
			anim.SetAnimation(jumpAtlas, 8, true);
			
		}
	}
	float x = grappPoint.x - GetCenter().x;
	float y = grappPoint.y - GetCenter().y;
	float mag = sqrtf(x * x + y * y);
	x /= mag;
	y /= mag;

	

	vel.x += x * dt * hookSpeed;
	vel.y += y * dt * hookSpeed;

	if (mag < 1.f || IsKeyPressed(KEY_SPACE))
	{
		RecoilJump();
	}

}

void Player::DanceCheck(float dt)
{
	if (status != STATUS::IDLE)
	{
		danceTimer = 0.f;
		isDancing = false;
		return;
	}
	danceTimer += dt;
	if (danceTimer > timeTillDance && !isDancing)
	{
		isDancing = true;
		anim.SetAnimation(danceAtlas, 8, true);
	}
}

void Player::PlaySoundWithPitchDiff(Sound sound)
{
	float randNum = (float)GetRandomValue(minPitch, maxPitch);
	randNum /= toRatio;
	SetSoundPitch(sound, randNum);
	PlaySound(sound);
}
