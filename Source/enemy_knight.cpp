#include "enemy_knight.h"

KnightEnemy::~KnightEnemy()
{
	 playerRef = nullptr; 

	 UnloadTexture(idleAtlas);
	 UnloadTexture(deathAtlas);
	 UnloadTexture(walkAtlas);
	 UnloadTexture(attack1Atlas);
	 UnloadTexture(attack2Atlas);
	 UnloadTexture(blockAtlas);

	 UnloadSound(deathSound);
	 UnloadSound(initAttackSound);
	 UnloadSound(swingAttackSound);
}

void KnightEnemy::SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D walkTxr, Texture2D attack1Txr, Texture2D attack2Txr, Texture2D blockTxr)
{
	idleAtlas = idleTxr;
	deathAtlas = deathTxr;
	walkAtlas = walkTxr;
	attack1Atlas = attack1Txr;
	attack2Atlas = attack2Txr;
	blockAtlas = blockTxr;
}

void KnightEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	deathSound = death;
	initAttackSound = init;
	swingAttackSound = swing;
}

void KnightEnemy::Setup()
{
	size.x = 80.f * scale;
	size.y = 64.f * scale;

	leftBorder.x = pos.x - 10;
	rightBorder.x = pos.x + 10;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;

	
	maxHealth = 50;
	health = maxHealth;
}

void KnightEnemy::Sense()
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
	if (lookRight && pos.x < playerRef->pos.x || !lookRight && pos.x > playerRef->pos.x)
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
	}
}

void KnightEnemy::Decide()
{
	if (dec == DECISION::DAMAGED)
	{
		return;
	}
	if (!hasAdvantage)
	{
		dec = DECISION::IDLE;
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
		switch (currentSlice)
		{
		case 1:
			anim.SetAnimation(attack1Atlas, 12, false);
			currentSlice = 2;
			break;
		case 2:
			anim.SetAnimation(attack2Atlas, 12, false);
			currentSlice = 1;
			break;
		}
		
		currentAttackId++;

	}
	else if (distance <= 10.f && lookRight && lDist > 1.f || distance <= 10.f && !lookRight && rDist > 1.f)
	{
		dec = DECISION::WALK;
		anim.SetAnimation(walkAtlas, 8, true);
	}
	else if(dec != IDLE)
	{
		dec = DECISION::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
	}
}

void KnightEnemy::Act(float dt)
{
	hitBox = { pos.x, pos.y - 1.f , 1.5f,2.f };
	hitBox.x = (lookRight) ? pos.x - 1.f : pos.x - 0.5f;
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
			anim.SetAnimation(idleAtlas, 8, true);
			if (health <= 0)
			{
				PlaySound(deathSound);
				SetIsAlive(false);
				anim.SetAnimation(deathAtlas, 8, false);
			}
		}
		break;
	}
}


void KnightEnemy::Render()
{
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 16.f , size.x, size.y };
	Vector2 origin = { dst.width / 2.f, dst.height * 0.75f };

	Color color = WHITE;
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::WALK:
		color = YELLOW;
		break;
	case DECISION::ATTACK:
		color = RED;
		break;
	}
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);


}

void KnightEnemy::CollisionCheck()
{
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (!playerRef->GetHit(pos, 10, currentAttackId))
		{
			health -= 10;
			UpdateAgroSwitch();
			dec = DAMAGED;
			anim.SetAnimation(blockAtlas, 5, false);
			
		}
	}
}

void KnightEnemy::Walk(float dt)
{
	if (lookRight )
	{
		pos.x -= dt * speed;
		return;
	}
	else if (!lookRight )
	{

	pos.x += dt * speed;
	}

}

void KnightEnemy::Attack(float dt)
{
	dt;
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{
	case 6:
		PlaySound(swingAttackSound);
		break;
	case 7:

		attackBox = { pos.x, pos.y - 1, 2, 2 };
		attackBox.x = (!lookRight) ? pos.x : pos.x - (attackBox.width);
		CollisionCheck();
		break;
	case 8:

		break;
	case 11:
		dec = DECISION::IDLE;

		break;
	}
}



void KnightEnemy::UpdateAgroSwitch()
{
	switchAgroCounter--;
	if (switchAgroCounter <= 0)
	{
		switchAgroCounter = 2;
		hasAdvantage = !hasAdvantage;

		if (!hasAdvantage)
		{
			dec = LOSTADVANTAGE;
			anim.SetAnimation(blockAtlas, 5, false);
		}
		if (hasAdvantage)
		{
			playerRef->LoseAdvantage();
		}
	}
}


bool KnightEnemy::GetHit(Vector2 sourcePos, int potentialDamage, int id)
{
	(void)sourcePos;
	if (dec == DAMAGED)
	{
		return false;
	}
	if (dec == ATTACK)
	{
		health -= static_cast<int>(potentialDamage / 2);
		return true;
	}
	dec = DAMAGED;
	anim.SetAnimation(blockAtlas, 5, false);

	UpdateAgroSwitch();



	health -= potentialDamage;
	lastAttackId = id;

	
	return true;
}



void KnightEnemy::RenderUI()
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

void KnightEnemy::Reset()
{
	SetIsAlive(true);
	anim.SetAnimation(idleAtlas, 8, false);
	health = maxHealth;
	pos = startPos;
	dec = IDLE;
}
