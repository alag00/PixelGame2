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

	leftBorder.x = pos.x - 10;
	rightBorder.x = pos.x + 10;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;


	maxHealth = 50;
	health = maxHealth;

	anim.SetAnimation(textures[0], 4, true);

	//anim.CustomFPS(6.f);
}

void GuardianEnemy::Sense()
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

void GuardianEnemy::Decide()
{
	if (dec == DECISION::DAMAGED)
	{
		return;
	}
	if (dec == DECISION::ATTACK)
	{
		return;
	}
	if (distance <= 1.5f)
	{
		dec = DECISION::ATTACK;
		PlaySound(initAttackSound);
		anim.SetAnimation(textures[2], 11, false);

	}
	else if (distance <= 10.f && lookRight && lDist > 1.f || distance <= 10.f && !lookRight && rDist > 1.f)
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
	anim.UpdateAnimator(dt);
	hitBox = { pos.x, pos.y - 1.f , 1.5f,2.f };
	hitBox.x = (lookRight) ? pos.x - 1.f : pos.x - 0.5f;
	hurtTimer -= dt;

	if (health <= 0)
	{
		PlaySound(deathSound);
		SetIsAlive(false);
		anim.SetAnimation(textures[5], 14, false);
		hurtTimer = 0.f;
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
