#include "enemy_statue.h"
WeepingAngelEnemy::~WeepingAngelEnemy()
{
	UnloadTexture(atlas);
}
void WeepingAngelEnemy::SetTextures(Texture2D txr)
{
	atlas = txr;
}
void WeepingAngelEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	death;
	init;
	swing;
}

void WeepingAngelEnemy::Setup()
{
	size.x = 32.f * scale;
	size.y = 32.f * scale;

	leftBorder.x = pos.x - 13;
	rightBorder.x = pos.x + 13;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;

	maxHealth = 10000;
	health = maxHealth;

	anim.SetAnimation(atlas, 3, true);
}

void WeepingAngelEnemy::Sense()
{
	bool playerLooksRight = playerRef->GetLookSide();

	if (pos.x > playerRef->GetCenter().x && !playerLooksRight || pos.x < playerRef->GetCenter().x && playerLooksRight)
	{
		active = true;
	}
	else
	{
		delayTimer = delay;
		active = false;
	}
	if (playerRef->GetCenter().x > rightBorder.x || playerRef->GetCenter().x < leftBorder.x)
	{
		delayTimer = delay;
		active = false;
	}

	if (lookLeft && pos.x < playerRef->GetCenter().x || !lookLeft && pos.x > playerRef->GetCenter().x)
	{
		if (delayTimer < 0.f)
		{

			lookLeft = !lookLeft;
			anim.FlipAnimationHorizontal();
		}
	}
}
void WeepingAngelEnemy::Decide()
{
	if (active && delayTimer < 0.f)
	{
		dec = DECISION::WALK;
	}
	else
	{
		dec = DECISION::IDLE;
	}
}
void WeepingAngelEnemy::Act(float dt)
{
	delayTimer -= (active) ? dt : 0.f;
	if(dec == DECISION::WALK)
	{ 
		Move(dt);
	}
}

void WeepingAngelEnemy::Move(float dt)
{
	anim.UpdateAnimator(dt);
	pos.x += (lookLeft)  ? -speed * dt : speed * dt;
	
	attackBox = { pos.x, pos.y - 1, 1, 2 };
	attackBox.x = (!lookLeft) ? pos.x : pos.x - (attackBox.width);

	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		playerRef->GetHit(pos, 10, 1);
		
	}
}

void WeepingAngelEnemy::Render()
{

	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 16.f , size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height *0.5f };

	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	DrawCircle(static_cast<int>(leftBorder.x * 64.f), static_cast<int>(leftBorder.y * 64.f), 6.f, PINK);
	DrawCircle(static_cast<int>(rightBorder.x * 64.f), static_cast<int>(rightBorder.y * 64.f), 6.f, PINK);

}