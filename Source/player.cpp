#include "player.h"

void Player::Unload()
{
	// Texture
	UnloadTexture(idleAtlas);
	UnloadTexture(walkAtlas);
	UnloadTexture(fallAtlas);
	UnloadTexture(jumpAtlas);
	UnloadTexture(ledgeAtlas);

	UnloadTexture(attackOneAtlas);
	UnloadTexture(attackTwoAtlas);
	UnloadTexture(deflectAtlas);
	UnloadTexture(successDeflectAtlas);
	UnloadTexture(damagedAtlas);
	UnloadTexture(loseAdvantageAtlas);

	UnloadTexture(deflectParticleAtlas);

	// Audio
	UnloadSound(hitSound);
	UnloadSound(deathSound);
	UnloadSound(jumpSound);
}

void Player::Setup()
{
	idleAtlas = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	walkAtlas = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	fallAtlas = LoadTexture("Assets/PlayerTextures/FallAtlas.png");
	jumpAtlas = LoadTexture("Assets/PlayerTextures/JumpAtlas.png");
	ledgeAtlas = LoadTexture("Assets/PlayerTextures/LedgeClimbAtlasAlter.png");

	attackOneAtlas = LoadTexture("Assets/PlayerTextures/FirstSliceAtlasAlter.png");
	attackTwoAtlas = LoadTexture("Assets/PlayerTextures/SecondSliceAtlas.png");
	deflectAtlas = LoadTexture("Assets/PlayerTextures/DeflectAtlas.png");
	airDeflectAtlas = LoadTexture("Assets/PlayerTextures/AirDeflectAtlas.png");
	successDeflectAtlas = LoadTexture("Assets/PlayerTextures/SuccessfulDeflectAtlas.png");
	damagedAtlas = LoadTexture("Assets/PlayerTextures/DamagedAtlas.png");
	loseAdvantageAtlas = LoadTexture("Assets/PlayerTextures/AdvantageLostAtlas.png");

	deflectParticleAtlas = LoadTexture("Assets/Particles/DeflectParticleAtlasAlter.png");


	hitSound = LoadSound("Assets/Audio/SFX/Hit.mp3");
	deathSound = LoadSound("Assets/Audio/SFX/PlayerDeath.mp3");
	jumpSound = LoadSound("Assets/Audio/SFX/Jump.mp3");

	anim.SetAnimation(idleAtlas, 8, true);
	particleAnim.SetAnimation(deflectParticleAtlas, 5, true);

	size.x = 48.f * scale;
	size.y = 48.f * scale;

	//pos.x = 1.f;
	//pos.y = 1.f;

	maxHealth = 30;
	health = maxHealth;
}

void Player::Update(float dt)
{
	UpdateParticles();
	anim.UpdateAnimator(dt);
	particleAnim.UpdateAnimator(dt);
	switch (status)
	{
	case STATUS::ATTACK: 
		Attack(dt);
		break;
	case STATUS::DAMAGED:
		DamageRecovery(dt);
		break;
	case STATUS::LOSTADVANTAGE:

		if (anim.GetCurrentFrame() >= 6)
		{
			status = STATUS::IDLE;
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
	dst = { pos.x * 64.f +  32.f, pos.y * 64.f + 40.f, size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	/*
	if (status == STATUS::ATTACK)
	{
		Color color = YELLOW;
		color.a = 50;
		DrawRectangle(attackBox.x * 64.f, attackBox.y * 64.f, attackBox.width * 64.f, attackBox.height * 64.f, color);
	}
	*/

	hitBox = { pos.x, pos.y, 1, 1 };
	RenderParticles();
}

void Player::Movement(float dt)
{	
	
	if (vel.y > 0.f && status != STATUS::FALLING && status != STATUS::DEFLECT)
	{
		anim.SetAnimation(fallAtlas, 4, true);
		status = STATUS::FALLING;
	}
	if (dt < 0.1f)
	{
		vel.y += (status != STATUS::FALLING) ? 20.f * dt : 30.f * dt;
	}
	

	jumpTimer += dt;
	fallingTimer += dt;

}

void Player::Control(float dt)
{


	if (status == STATUS::DEFLECT && !onGround)
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
		if (anim.GetCurrentFrame() < 4)
		{
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

			if (fallingTimer > 0.f && fallingTimer < 0.1f)
			{
				Jump();
			}

			jumpTimer = 0.f;
		}
	}
	if (IsKeyDown(KEY_A))
	{
		vel.x = -10.f;
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
		vel.x = 10.f;
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
		if (status != STATUS::JUMPING && status != STATUS::FALLING)
		{
			anim.SetAnimation(deflectAtlas, 5, true);
		}
		else
		{
			anim.SetAnimation(airDeflectAtlas, 5, true);
		}
		status = STATUS::DEFLECT;
	}
}

void Player::LedgeJump(Vector2 edgePoint)
{
	anim.SetAnimation(ledgeAtlas, 7, true);
	onGround = false;
	status = STATUS::JUMPING;

	float dx = edgePoint.x - pos.x;
	float dy = edgePoint.y - pos.y;

	float mag = sqrtf((dx * dx) + (dy * dy));
	dx /= mag;
	dy /= mag;

	vel.x = dx * ledgeJumpPower;
	vel.y = -ledgeJumpPower;

	if (lookRight &&  pos.x > edgePoint.x || !lookRight && pos.x < edgePoint.x)
	{
		anim.FlipAnimationHorizontal();
		particleAnim.FlipAnimationHorizontal();
		lookRight = !lookRight;
	}
}

void Player::Jump()
{
	anim.SetAnimation(jumpAtlas, 8, true);
	onGround = false;
	status = STATUS::JUMPING;
	vel.y = -maxJumpPower / 5.f;
	PlaySound(jumpSound);
	
}
void Player::SetOnGround(bool newValue)
{
	onGround = newValue;
	
	if (onGround)
	{
		jumpCounter = 0.f;
		fallingTimer = 0.f;
		if (jumpTimer > 0.f && jumpTimer <= 0.1f)
		{
			Jump();
		}
		if (status != STATUS::MOVING && status != STATUS::DEFLECT && status != STATUS::ATTACK)
		{
			vel.y = 0.f;
			anim.SetAnimation(idleAtlas, 8, true);
			status = STATUS::IDLE;
		}
	}
}
void Player::Attack(float dt)
{
	vel.y += 20.f * dt;
	if (IsKeyPressed(KEY_O))
	{
		queuedAttack = true;
	}
	switch (anim.GetCurrentFrame())
	{
	case 0:
		vel.x = (lookRight) ? 1.f : -1.f;
		break;
	case 1:
		vel.x = (lookRight) ? 4.f : -4.f;
		break;
	case 2:
		vel.x = (lookRight) ? 4.f : -4.f;
		break;
	case 3:
		vel.x = (lookRight) ? 1.f : -1.f;
		break;
	case 4:
		attackBox = { pos.x, pos.y, 1, 1 };
		attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);

		break;
	case 5:
		attackBox = { pos.x, pos.y, 1, 1 };
		attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);

		break;
	case 6:
		vel.x = 0.f;
		status = STATUS::IDLE;
		attackBox.width = 0.f;
		attackBox.height = 0.f;

		if (queuedAttack)
		{
			InitAttack();
		}

		break;
	}
	
	
}


bool Player::CollisionCheck(Entity& enemy)
{
	if (status == STATUS::ATTACK && anim.GetCurrentFrame() <= 5 && anim.GetCurrentFrame() >= 4)
	{

		if (CheckCollisionRecs(attackBox, enemy.hitBox))
		{
			status = STATUS::IDLE;
			playParticle = true;

			vel.x = (lookRight) ? -15.f : 15.f;

			enemy.GetHit(pos, 10, currentAttackId);
		
			attackBox.width = 0.f;
			attackBox.height = 0.f;

			float randNum = (float)GetRandomValue(80, 120);
			randNum /= 100.f;
			SetSoundPitch(hitSound, randNum);
			PlaySound(hitSound);
			return true;
		}

	}
	return false;
}

bool Player::IsInAttackMode()
{
	if (status != STATUS::ATTACK)
	{
		return false;
	}
	return true;
}

bool Player::GetHit(Vector2 sourcePos, int potentialDamage, int id)
{
	if (status == STATUS::DAMAGED)
	{
		return true;
	}
	(void)id;

	float randNum = (float)GetRandomValue(80, 120);
	randNum /= 100.f;
	SetSoundPitch(hitSound, randNum);
	PlaySound(hitSound);
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
	vel.x = (sourcePos.x > pos.x) ? -15.f : 15.f;
	playParticle = true;

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
	Rectangle dst = { pos.x, pos.y, size.x, size.y };
	dst = { pos.x * 64.f + 32.f, pos.y * 64.f + 40.f, size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };

	dst.x = (lookRight) ? dst.x + 16.f : dst.x - 16.f;
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
		
	}
	else
	{
		// Air Attack
	}
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