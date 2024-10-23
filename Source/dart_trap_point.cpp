#include "dart_trap_point.h"

DartTrap::~DartTrap()
{

	
}

void DartTrap::Setup(Vector2 newPos, Entity& ref, bool left)
{
	
	pos = newPos;
	playerRef = &ref;

	speed = (left) ? -speed : speed ;
	if (!left)
	{
		anim.FlipAnimationHorizontal();
	}
}

void DartTrap::SetTexture(Texture2D txr)
{
	anim.SetAnimation(txr, 4, true);
}

void DartTrap::Update(float dt)
{
	anim.UpdateAnimator(dt);
	timeAlive -= dt;
	if (timeAlive < 0.f)
	{
		bulletPos = pos;
		timeAlive = FULL_TIME_ALIVE;
		active = true;
	}
	
	if (active)
	{

		bulletPos.x += dt * speed;
	}
	


	Rectangle bulletBox{bulletPos.x, bulletPos.y, BULLET_TILE_WIDTH, BULLET_TILE_HEIGHT};
	if (CheckCollisionRecs(playerRef->hitBox, bulletBox))
	{
		playerRef->GetHit(bulletPos, ATTACK_DAMAGE);
		bulletPos = pos;
		active = false;
		
	}
}

void DartTrap::Render(Rectangle cam)
{
	Rectangle dst{bulletPos.x * config.tileSize, bulletPos.y * config.tileSize, BULLET_PIXEL_WIDTH * config.pixelScale, BULLET_PIXEL_HEIGHT * config.pixelScale};
	if (!active || !CheckCollisionRecs(cam, dst))
	{
		return;
	}
	Vector2 origin{0.f,0.f};
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

}
