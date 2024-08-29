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


	maxHealth = 10000;
	health = maxHealth;

	anim.SetAnimation(atlas, 3, true);
}

void WeepingAngelEnemy::Sense()
{
	bool playerLooksRight = playerRef->GetLookSide();
	active = false;
	if (pos.x > playerRef->GetCenter().x && !playerLooksRight || pos.x < playerRef->GetCenter().x && playerLooksRight)
	{
		active = true;
	}

	if (lookLeft && pos.x < playerRef->pos.x || !lookLeft && pos.x > playerRef->pos.x)
	{
		lookLeft = !lookLeft;
		anim.FlipAnimationHorizontal();
	}
}
void WeepingAngelEnemy::Decide()
{
	if (active)
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
	if(dec == DECISION::WALK)
	{ 
		Move(dt);
	}
}

void WeepingAngelEnemy::Move(float dt)
{
	anim.UpdateAnimator(dt);
	pos.x += (lookLeft)  ? -1.f * dt : 1.f * dt;
	

}

void WeepingAngelEnemy::Render()
{

	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 16.f , size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height *0.5f };

	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	Rectangle testBox{ attackBox.x * 64.f, attackBox.y * 64.f,attackBox.width * 64.f ,attackBox.height * 64.f };
	Color color = YELLOW;
	color.a = 50;
	DrawRectangleRec(testBox, color);
}