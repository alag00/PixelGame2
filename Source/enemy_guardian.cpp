#include "enemy_guardian.h"

GuardianEnemy::~GuardianEnemy()
{
	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(textures[i]);
	}
	UnloadSound(deathSound);
	UnloadSound(initAttackSound);
	UnloadSound(swingAttackSound);
}

void GuardianEnemy::SetTextures(Texture2D txr[])
{
	for (int i = 0; i < 6; i++)
	{
		textures[i] = txr[i];
	}
}

void GuardianEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	deathSound = death;
	initAttackSound = init;
	swingAttackSound = swing;
}

void GuardianEnemy::Setup()
{
	size.x = 112.f * scale;
	size.y = 112.f * scale;

	leftBorder.x = pos.x - 19;
	rightBorder.x = pos.x + 17;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;


	maxHealth = 100;
	health = maxHealth;

	anim.SetAnimation(textures[0], 4, true);

	anim.CustomFPS(SLOW_FRAME_RATE);
}

void GuardianEnemy::Sense()
{
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf((x * x) + (y * y));

	rDist = rightBorder.x - pos.x;
	lDist = pos.x - leftBorder.x;
	if (dec == DECISION::ATTACK || dec == DECISION::GRAB || grabbing)
	{
		return;
	}
	if (lookRight && pos.x < playerRef->GetCenter().x || !lookRight && pos.x > playerRef->GetCenter().x)
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
	}
}

void GuardianEnemy::Decide()
{
	if (dec == DECISION::ATTACK || dec == DECISION::GRAB || grabbing)
	{
		return;
	}
	if (cooldownTimer > 0.f)
	{
		return;
	}
	if (distance <= 3.f)
	{
		
		PlaySound(initAttackSound);
		anim.SetAnimation(textures[2], 11, false);

		int randNum = GetRandomValue(0, 10);
		if (randNum < 6)
		{
			dec = DECISION::ATTACK;
			anim.SetAnimation(textures[2], 11, false);
		}
		else
		{
			pauseTimer = PAUSE_TIME;
			dec = DECISION::GRAB;
			anim.SetAnimation(textures[3], 10, false);
		}

	}
	else if ( lookRight && lDist > 1.f ||  !lookRight && rDist > 1.f)
	{
		dec = DECISION::WALK;
		anim.SetAnimation(textures[1], 8, true);
	}
	else if (dec != IDLE)
	{
		dec = DECISION::IDLE;
		anim.SetAnimation(textures[0], 4, true);
	}
}

void GuardianEnemy::Act(float dt)
{
	if (dec != DECISION::GRAB)
	{
		anim.UpdateAnimator(dt);
	}
	hitBox = { pos.x, pos.y, 2.f, 4.f };
	hitBox.y -= hitBox.height * 0.5f;
	hitBox.x = pos.x - 1.f;
	hurtTimer -= dt;
	cooldownTimer -= dt;

	if (health <= 0)
	{
		PlaySound(deathSound);
		SetIsAlive(false);
		anim.SetAnimation(textures[5], 14, false);
		anim.CustomFPS(12.f);
		hurtTimer = 0.f;
	}
	if (grabbing)
	{
		GrabHit(dt);
		return;
	}
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::WALK:
		Walk(dt);
		break;
	case DECISION::ATTACK:
		Attack(dt);
		break;
	case DECISION::GRAB:
		GrabDash(dt);
		break;
	}
}

void GuardianEnemy::Render()
{
	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
	}
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f - 16.f , size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height * 0.75f };


	Color color = (hurtTimer <= 0.f) ? WHITE : RED;
	anim.DrawAnimationPro(dst, origin, 0.f, color);
}

void GuardianEnemy::CollisionCheck()
{

	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (dec == GRAB)
		{
			grabbing = true;
			anim.SetAnimation(textures[4], 10, false);
			dec = IDLE;
			return;
		}
		if (!playerRef->GetHit(pos, ATTACK_DAMAGE))
		{
			health -= DEFLECTED_DAMAGE;
			anim.SetAnimation(textures[0], 4, true);
			dec = IDLE;
		}
		cooldownTimer = ATTACK_COOLDOWN_TIME;
	}
}

void GuardianEnemy::Walk(float dt)
{
	if (lookRight)
	{
		pos.x -= dt * speed;
		return;
	}
	else if (!lookRight)
	{

		pos.x += dt * speed;
	}
}

void GuardianEnemy::Attack(float dt)
{
	dt;
	if (anim.GetCurrentFrame() == 7 || anim.GetCurrentFrame() == 8)
	{
		attackBox = { pos.x, pos.y, 2.5f, 4.f };
		attackBox.y -= attackBox.height - 1;
		attackBox.x = (lookRight) ? attackBox.x - attackBox.width: attackBox.x;
		CollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 10)
	{
		anim.SetAnimation(textures[0], 4, true);
		dec = IDLE;
		cooldownTimer = ATTACK_COOLDOWN_TIME;
	}
}

void GuardianEnemy::GrabDash(float dt)
{
	if (anim.GetCurrentFrame() == 1)
	{
		pauseTimer -= dt;
		if (pauseTimer > 0.f)
		{
			return;
		}
	}
	anim.UpdateAnimator(dt);
	if (anim.GetCurrentFrame() >= 2 && anim.GetCurrentFrame() <= 7)
	{
		if (lookRight && lDist > 1.f)
		{
			pos.x -= dt * DASH_SPEED;
		}
		else if (!lookRight && rDist > 1.f)
		{

			pos.x += dt * DASH_SPEED;
		}
		attackBox = { pos.x, pos.y, 2.5f, 2.f };
		attackBox.y -= attackBox.height - 1;
		attackBox.x = (lookRight) ? attackBox.x - attackBox.width : attackBox.x;
		CollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 9)
	{
		
		anim.SetAnimation(textures[0], 4, true);
		dec = IDLE;
		
	}
}

void GuardianEnemy::GrabHit(float dt)
{

	grabProgress += dt;

	float procent = grabProgress / (3.f / SLOW_FRAME_RATE);
	if (anim.GetCurrentFrame() >= 0 && anim.GetCurrentFrame() < 3)
	{
		playerRef->pos.y = std::lerp(pos.y - 1.f, pos.y - 1.5f, procent);
		playerRef->pos.x = (lookRight) ? std::lerp(pos.x - 0.5f, pos.x + 0.5f, procent) : std::lerp(pos.x + 1.f, pos.x - 1.f, procent);
	}
	
	if (anim.GetCurrentFrame() >= 3 && anim.GetCurrentFrame() <= 8)
	{
		playerRef->pos.y = pos.y - 1.5f;
		playerRef->pos.x = (lookRight) ? pos.x + 0.5f : pos.x - 1.f;
		
	}
	if (anim.GetCurrentFrame() >= 9)
	{
		playerRef->GetHit(pos, ATTACK_DAMAGE);
		anim.SetAnimation(textures[0], 4, true);
		dec = IDLE;
		grabbing = false;
		grabProgress = 0.f;
	}
}

bool GuardianEnemy::GetHit(Vector2 sourcePos, int potentialDamage)
{
	sourcePos;

	if (hurtTimer > 0.f)
	{
		return false;
	}

	health -= potentialDamage;
	hurtTimer = HURT_TIME;
	return true;
}

void GuardianEnemy::RenderUI()
{
	if (isBoss)
	{
		return;
	}
	Rectangle blackBar{ pos.x * 64.f - 64.f, pos.y * 64.f + 64.f + 16.f , 128.f, 16.f };
	DrawRectangleRec(blackBar, BLACK);

	float margin = 3.f;
	Rectangle remainingHealth = { blackBar.x + margin,blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f };
	float percent = (float)health / (float)maxHealth;
	remainingHealth.width *= percent;

	DrawRectangleRec(remainingHealth, GREEN);

}

void GuardianEnemy::Reset()
{
	if (isBoss && !IsAlive())
	{
		return;
	}
	SetIsAlive(true);
	anim.SetAnimation(textures[0], 4, false);
	health = maxHealth;
	pos = startPos;
	dec = IDLE;
}
