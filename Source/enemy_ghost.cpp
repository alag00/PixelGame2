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

	yOrigin = pos.y;
}

void GhostEnemy::Sense()
{
	if (!dashMode)
	{
		if (!lookRight && pos.x > playerRef->GetCenter().x || lookRight && pos.x < playerRef->GetCenter().x)
		{
			lookRight = !lookRight;
			anim.FlipAnimationHorizontal();
		}
	}

	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf(x * x + y * y);

}

void GhostEnemy::Decide()
{
	if (dashMode)
	{
		return;
	}
	if (!isHunting && distance <= HUNT_RADIUS)
	{
		isHunting = true;
	}
	if (distance <= DASH_RADIUS)
	{
		dashMode = true;
		waitTimer = WAIT_TIME / 2.f;
		
		dashDir.x = GetCenter().x - playerRef->GetCenter().x;
		dashDir.y = GetCenter().y - playerRef->GetCenter().y;
		float mag = sqrtf(dashDir.x * dashDir.x + dashDir.y * dashDir.y);

		dashDir.x /= -mag;
		dashDir.y /= -mag;

		
	}
}

void GhostEnemy::Act(float dt)
{
	hoverProgress += dt;
	pos.y = yOrigin + sin(hoverProgress) / 2.f;
	if (!isHunting)
	{
		return;
	}
	if (dashMode)
	{
		DashAttack(dt);
		return;
	}
	if (waitTimer > 0.f)
	{
		waitTimer -= dt;
		return;
	}
	
	Move(dt, playerRef->GetCenter(), SPEED);
}

void GhostEnemy::Render()
{

	Color currentColor = (dashMode) ? ATTACK_COLOR : NORMAL_COLOR;

	Rectangle dst = { pos.x * 64.f, pos.y * 64.f, size.x, size.y };
	Vector2 origin{ 0.f,0.f };
	anim.DrawAnimationPro(dst, origin, 0.f, currentColor);

	
	
}

void GhostEnemy::CollisionCheck()
{
	if (CheckCollisionRecs(playerRef->hitBox, hitBox))
	{
		playerRef->GetHit(pos, ATTACK_DAMAGE);
		dashMode = false;
		waitTimer = WAIT_TIME;
		dashTimer = DASH_TIME;
	}
}

void GhostEnemy::Move(float dt, Vector2 destination, float speed)
{
	float x = GetCenter().x - destination.x;
	float y = GetCenter().y - destination.y;
	float mag = sqrtf(x * x + y * y);

	x /= -mag;
	y /= -mag;

	pos.x += x * dt * speed;
	yOrigin += y * dt * speed;
	

	
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

void GhostEnemy::DashAttack(float dt)
{
	waitTimer -= dt;
	if (waitTimer > 0.f)
	{
		return;
	}
	//Move(dt, dashDir, SPEED * 4.f);
	pos.x += dashDir.x * dt * SPEED * 4.f;
	yOrigin += dashDir.y * dt * SPEED * 4.f;


	hitBox.x = pos.x;
	hitBox.y = pos.y;
	CollisionCheck();
	dashTimer -= dt;
	if (dashTimer <= 0.f)
	{
		dashMode = false;
		waitTimer = WAIT_TIME;
		dashTimer = DASH_TIME;
	}
}
