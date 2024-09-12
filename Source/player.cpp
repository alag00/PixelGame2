#include "player.h"

void Player::Unload()
{
	// Texture
	UnloadTexture(idleAtlas);
	UnloadTexture(walkAtlas);
	UnloadTexture(fallAtlas);
	UnloadTexture(jumpAtlas);
	UnloadTexture(ledgeAtlas);
	UnloadTexture(climbAtlas);
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
	climbAtlas = LoadTexture("Assets/PlayerTextures/ClimbAtlas.png");
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

	anim.SetAnimation(idleAtlas, 8, true);
	particleAnim.SetAnimation(deflectParticleAtlas, 5, true);

	size.x = 48.f * scale;
	size.y = 48.f * scale;

	//pos.x = 1.f;
	//pos.y = 1.f;

	maxHealth = 100;
	health = maxHealth;
}

void Player::Update(float dt)
{
	UpdateParticles();
	anim.UpdateAnimator(dt);
	particleAnim.UpdateAnimator(dt);
	DanceCheck(dt);
	hitBox = { pos.x, pos.y, 1, 1 };
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
		vel.y += 20.f * dt;
		QueueAttackCheck();
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
		vel.y += 35.f * dt;
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
	dst = { pos.x * 64.f +  32.f, pos.y * 64.f + 40.f, size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	
	if (status == STATUS::ATTACK || status == STATUS::AIRATTACK)
	{
		Color color = YELLOW;
		color.a = 50;
		Rectangle debugBox = { attackBox.x * 64.f, attackBox.y * 64.f,attackBox.width * 64.f ,attackBox.height * 64.f };
		DrawRectangleRec(debugBox, color);
		//DrawRectangle(attackBox.x * 64.f, attackBox.y * 64.f, attackBox.width * 64.f, attackBox.height * 64.f, color);
	}
	


	RenderParticles();
	/*
	Color color = YELLOW;
	color.a = 50;
	Rectangle box = { hitBox.x * 64.f, hitBox.y * 64.f,hitBox.width * 64.f ,hitBox.height * 64.f };
	DrawRectangleRec(box, color);
	*/
	if (status == STATUS::HOOK)
	{
		Vector2 vec1 = { GetCenter().x * 64.f, GetCenter().y * 64.f };
		vec1.x += (lookRight) ? 32.f: -32.f;
		Vector2 vec2 = { grappPoint.x * 64.f, grappPoint.y * 64.f };
		DrawLineBezier(vec1, vec2, 5.f, YELLOW);
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
		vel.y += (status != STATUS::FALLING) ? 20.f * dt : 30.f * dt;
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
	if (IsKeyReleased(KEY_SPACE) && status == STATUS::JUMPING)
	{
		vel.y = (vel.y < -5.f) ? -5.f: vel.y;
		//vel.y = -5.f;
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
		if (onGround)//(status != STATUS::JUMPING && status != STATUS::FALLING)
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

void Player::RecoilJump()
{
	status = STATUS::AIRMOVEMENT;
	anim.SetAnimation(jumpAtlas, 8, true);
	vel.y = -7.f;
	vel.x = (lookRight) ? 10.f : -10.f;
	/*
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
	*/
}

void Player::Jump()
{
	anim.SetAnimation(jumpAtlas, 8, true);
	onGround = false;
	status = STATUS::JUMPING;
	vel.y = -maxJumpPower / 5.f;

	float randNum = (float)GetRandomValue(80, 120);
	randNum /= 100.f;
	SetSoundPitch(jumpSound, randNum);
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
		
		else if (status == STATUS::FALLING || status == STATUS::AIRRECOVERY || status == STATUS::AIRATTACK || status == STATUS::AIRMOVEMENT)
		{
			vel.y = 0.f;
			status = STATUS::IDLE;

			anim.SetAnimation(idleAtlas, 8, true);
		}
		/*
		else if (status != STATUS::MOVING && status != STATUS::DEFLECT && status != STATUS::ATTACK)
		{
			vel.y = 0.f;
			status = STATUS::IDLE;
			
			anim.SetAnimation(idleAtlas, 8, true);
		}
		*/
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
		//attackBox = { pos.x, pos.y, 2, 2 };
		//attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);

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
void Player::AirAttack(float dt)
{
	vel.y += 20.f * dt;
	attackBox = { pos.x, pos.y, 1, 1 };
	attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);
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
				playParticle = true;

				vel.x = (lookRight) ? -20.f : 20.f;

				enemy.GetHit(pos, 10, currentAttackId);

				attackBox.width = 0.f;
				attackBox.height = 0.f;

				float randNum = (float)GetRandomValue(80, 120);
				randNum /= 100.f;
				SetSoundPitch(hitSound, randNum);
				PlaySound(hitSound);

				LoseAdvantage();
				/*
				if (queuedAttack)
				{
					InitAttack();
				}
				*/
				return true;
			}

		}
		break;
	case  STATUS::AIRATTACK:
		if (CheckCollisionRecs(attackBox, enemy.hitBox))
		{
			
			playParticle = true;
			enemy.GetHit(pos, 10, currentAttackId);

			status = STATUS::AIRRECOVERY;
			anim.SetAnimation(jumpAtlas, 8, true);
			vel.y = -7.f;
			vel.x = (lookRight) ? 10.f : -10.f;
			//vel.x = (lookRight) ? -15.f : 15.f;




			attackBox.width = 0.f;
			attackBox.height = 0.f;

			float randNum = (float)GetRandomValue(80, 120);
			randNum /= 100.f;
			SetSoundPitch(hitSound, randNum);
			PlaySound(hitSound);
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
	if (IsKeyPressed(KEY_O))
	{
		queuedAttack = true;
	}
	else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
	{
		queuedAttack = false;
	}
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
	vel.x = (sourcePos.x > pos.x) ? -20.f : 20.f;
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
		attackBox = { pos.x, pos.y - 0.5f , 2.f, 1.5 };
		attackBox.x = (!lookRight) ? pos.x - 1.f : pos.x;
	}
	else
	{
		anim.SetAnimation(airAttackAtlas, 4, true);
		status = STATUS::AIRATTACK;
		vel.x = (lookRight) ? 10.f : -10.f;
		vel.y = -5.f;

		float randNum = (float)GetRandomValue(80, 120);
		randNum /= 100.f;
		SetSoundPitch(jumpSound, randNum);
		PlaySound(jumpSound);
		attackBox = { pos.x, pos.y, 1, 1 };
		attackBox.x = (!lookRight) ? pos.x - (attackBox.width) : pos.x + (attackBox.width);
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


void Player::EnterClimbMode()
{
	status = STATUS::CLIMB;
	anim.SetAnimation(climbAtlas, 8, true);
}
void Player::ClimbControl(float dt)
{
	dt;
	vel = { 0.f,0.f };
	if (IsKeyPressed(KEY_SPACE))
	{
		//Jump();
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
		particleAnim.FlipAnimationHorizontal();
		RecoilJump();
		vel.y += -3.f;
		//vel.x = (lookRight) ? -10.f : 10.f;
	}
	else if (IsKeyDown(KEY_S))
	{
		vel.y = 3;
		if (IsKeyDown(KEY_A) && lookRight || IsKeyDown(KEY_D) && !lookRight)
		{
			lookRight = !lookRight;
			anim.FlipAnimationHorizontal();
			particleAnim.FlipAnimationHorizontal();
			status = STATUS::FALLING;
			anim.SetAnimation(fallAtlas, 4, true);
		}
	}
	
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

	float hookSpeed = 25.f;

	vel.x += x * dt * hookSpeed;
	vel.y += y * dt * hookSpeed;

	if (mag < 1.f || IsKeyPressed(KEY_SPACE))
	{
		RecoilJump();
		//status = STATUS::AIRRECOVERY;
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
	if (danceTimer > 5.f && !isDancing)
	{
		isDancing = true;
		anim.SetAnimation(danceAtlas, 8, true);
	}
}
