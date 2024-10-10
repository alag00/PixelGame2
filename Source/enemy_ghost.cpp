#include "enemy_ghost.h"

GhostEnemy::~GhostEnemy()
{
	UnloadTexture(idleAtlas);
}

void GhostEnemy::SetTextures(Texture2D idleTxr)
{
	idleAtlas = idleTxr;
}

void GhostEnemy::Setup()
{
	size.x = 16.f * scale;
	size.y = 32.f * scale;

	anim.SetAnimation(idleAtlas, 1, false);

	hitBox = { pos.x, pos.x, 1, 2 };

}

void GhostEnemy::Sense()
{
	if (isHunting)
	{
		if (!lookRight && pos.x > playerRef->GetCenter().x || lookRight && pos.x < playerRef->GetCenter().x)
		{
			lookRight = !lookRight;
			anim.FlipAnimationHorizontal();
		}
		return;
	}
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	float mag = sqrtf(x * x + y * y);
	if(mag <= HUNT_RADIUS)
	{
		isHunting = true;

	}
}

void GhostEnemy::Decide()
{
	if (!isHunting)
	{
		return;
	}
}

void GhostEnemy::Act(float dt)
{
	if (!isHunting)
	{
		return;
	}
	if (waitTimer > 0.f)
	{
		waitTimer -= dt;
		return;
	}
	hitBox.x = pos.x;
	hitBox.y = pos.y;
	Move(dt);
	CollisionCheck();
}

void GhostEnemy::Render()
{

	Color currentColor = (waitTimer <= 0.f && isHunting) ? ATTACK_COLOR : NORMAL_COLOR;

	Rectangle dst = { pos.x * 64.f, pos.y * 64.f, size.x, size.y };
	Vector2 origin{ 0.f,0.f };
	anim.DrawAnimationPro(dst, origin, 0.f, currentColor);

	
	
}

void GhostEnemy::CollisionCheck()
{
	if (CheckCollisionRecs(playerRef->hitBox, hitBox))
	{
		playerRef->GetHit(pos, ATTACK_DAMAGE);
		waitTimer = WAIT_TIME;
	}
}

void GhostEnemy::Move(float dt)
{
	float x = GetCenter().x - playerRef->GetCenter().x;
	float y = GetCenter().y - playerRef->GetCenter().y;
	float mag = sqrtf(x * x + y * y);

	x /= -mag;
	y /= -mag;

	pos.x += x * dt * SPEED;
	pos.y += y * dt * SPEED;
}

void GhostEnemy::Reset()
{
	pos = startPos;
	isHunting = false;
}

Vector2 GhostEnemy::GetCenter()
{
	return Vector2(pos.x + 0.5f, pos.y + 1.f);
}
