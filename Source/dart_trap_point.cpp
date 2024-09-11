#include "dart_trap_point.h"

void DartTrap::Setup(Vector2 newPos, Entity& ref, Texture2D atlas, bool left)
{
	anim.SetAnimation(atlas, 4, true);
	pos = newPos;
	playerRef = &ref;

	speed = (left) ? -speed : speed ;
}

void DartTrap::Update(float dt)
{
	anim.UpdateAnimator(dt);
	timeAlive -= dt;
	if (timeAlive < 0.f)
	{
		bulletPos = pos;
		timeAlive = 3.f;
	}
	bulletPos.x += dt * speed;


	Rectangle bulletBox{bulletPos.x, bulletPos.y, 2.f, 1.f};
	if (CheckCollisionRecs(playerRef->hitBox, bulletBox))
	{
		playerRef->GetHit(bulletPos, 10, 1);
		bulletPos = pos;
		//timeAlive = 3.f;
	}
}

void DartTrap::Render()
{
	Rectangle dst{bulletPos.x * 64.f, bulletPos.y * 64.f, 32.f * 3.f, 16.f* 3.f};
	Vector2 origin{0.f,0.f};
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

}
