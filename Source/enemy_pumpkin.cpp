#include "enemy_pumpkin.h"

PumpkinEnemy::~PumpkinEnemy()
{
	playerRef = nullptr;

	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(textures[i]);
	}

	UnloadSound(deathSound);
	UnloadSound(initAttackSound);
	UnloadSound(swingAttackSound);
}

void PumpkinEnemy::SetTextures(Texture2D txr[])
{
	for (int i = 0; i < 6; i++)
	{
		textures[i] = txr[i];
	}
}

void PumpkinEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	deathSound = death;
	initAttackSound = init;
	swingAttackSound = swing;
}

void PumpkinEnemy::Setup()
{
	size.x = 48.f * scale;
	size.y = 48.f * scale;

	leftBorder.x = pos.x - 10;
	rightBorder.x = pos.x + 10;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;


	maxHealth = 80;
	health = maxHealth;

	anim.SetAnimation(textures[0], 8, true);
}

void PumpkinEnemy::Sense()
{
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf((x * x) + (y * y));

	rDist = rightBorder.x - pos.x;
	lDist = pos.x - leftBorder.x;
	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED)
	{
		return;
	}
	if (lookRight && pos.x < playerRef->GetCenter().x || !lookRight && pos.x > playerRef->GetCenter().x)
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
	}
}

void PumpkinEnemy::Decide()
{
	if (dec == DECISION::DAMAGED)
	{
		return;
	}

	if (dec == DECISION::ATTACK)
	{
		return;
	}
	if (distance <= 1.5f && cooldownTimer <= 0.f)
	{
		dec = DECISION::ATTACK;
		anim.SetAnimation(textures[2], 10, false);
		PlaySound(initAttackSound);
		currentAttackStage = 1;

	

	}
	else if (distance <= 10.f && lookRight && lDist > 1.f || distance <= 10.f && !lookRight && rDist > 1.f)
	{
		dec = DECISION::WALK;
		anim.SetAnimation(textures[1], 8, true);
	}
	else if (dec != IDLE)
	{
		dec = DECISION::IDLE;
		anim.SetAnimation(textures[0], 8, true);
	}
}

void PumpkinEnemy::Act(float dt)
{
	anim.UpdateAnimator(dt);
	hitBox = { pos.x, pos.y - 1.f , 1.5f,2.f };
	hitBox.x = (lookRight) ? pos.x - 1.f : pos.x - 0.5f;
	cooldownTimer -= dt;
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
	case DECISION::DAMAGED:
		if (anim.GetCurrentFrame() >= 4)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(textures[0], 8, true);
			if (health <= 0)
			{
				PlaySound(deathSound);
				SetIsAlive(false);
				anim.SetAnimation(textures[5], 6, false);
			}
		}
		break;
	}
}


void PumpkinEnemy::Render()
{
	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
	}
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 64.f  , size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height};

	
	Color color = (dec != DAMAGED) ? WHITE : RED;
	anim.DrawAnimationPro(dst, origin, 0.f, color);

}

void PumpkinEnemy::CollisionCheck()
{
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (!playerRef->GetHit(pos, ATTACK_DAMAGE))
		{
			health -= DEFLECTED_DAMAGE;
			spinCollisionTimer = SPIN_COLLISION_TIME;
			if (health <= 0)
			{
				dec = DAMAGED;
				anim.SetAnimation(textures[4], 5, false);
			}
			
		}
	}
}

void PumpkinEnemy::Walk(float dt)
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

void PumpkinEnemy::Attack(float dt)
{
	dt;
	int currentFrame = anim.GetCurrentFrame();

	if (currentAttackStage == 1)
	{
		if (currentFrame >= 9)
		{
			currentAttackStage = 2;
			anim.SetAnimation(textures[3], 4, true);
			spinTimer = spinTime;
			spinCollisionTimer = 0.f;
		}
		return;
	}
	if (lookRight)
	{
		pos.x -= dt * speed * 0.5f;
	}
	else if (!lookRight)
	{

		pos.x += dt * speed * 0.5f;
	}
	if (pos.x < leftBorder.x + SPIN_WALL_STOP_OFFSET)
	{
		pos.x = leftBorder.x + SPIN_WALL_STOP_OFFSET;
	}
	if (pos.x > rightBorder.x - SPIN_WALL_STOP_OFFSET)
	{
		pos.x = rightBorder.x - SPIN_WALL_STOP_OFFSET;
	}
	spinTimer -= dt;

	spinCollisionTimer -= dt;
	if (spinCollisionTimer <= 0.f)
	{
		attackBox = { pos.x - 1, pos.y - 0.5f , 2, 1.5f };
		CollisionCheck();
	}
	if (spinTimer <= 0.f)
	{
		dec = IDLE;
		anim.SetAnimation(textures[0], 8, true);
		cooldownTimer = ATTACK_COOLDOWN;
	}

}




bool PumpkinEnemy::GetHit(Vector2 sourcePos, int potentialDamage)
{
	(void)sourcePos;
	if (dec == DAMAGED)
	{
		return false;
	}
	if (dec == ATTACK)
	{
		health -= static_cast<int>(potentialDamage / 2);
		if (health <= 0)
		{
			dec = DAMAGED;
			anim.SetAnimation(textures[4], 5, false);
		}
		return true;
	}
	dec = DAMAGED;
	anim.SetAnimation(textures[4], 5, false);

	



	health -= potentialDamage;


	return true;
}



void PumpkinEnemy::RenderUI()
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

void PumpkinEnemy::Reset()
{
	if (isBoss && !IsAlive())
	{
		return;
	}
	SetIsAlive(true);
	anim.SetAnimation(textures[0], 8, false);
	health = maxHealth;
	pos = startPos;
	dec = IDLE;
}
