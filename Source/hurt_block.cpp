#include "hurt_block.h"

void HurtBlock::Setup(Vector2 newPos, Entity& ref)
{
	centerPos.x = newPos.x + CENTER_OFFSET;
	centerPos.y = newPos.y + CENTER_OFFSET;

	playerRef = &ref;

	
	lPos = { centerPos.x - CENTER_OFFSET, centerPos.y + CENTER_OFFSET };
	mPos = { centerPos.x, newPos.y + HIT_PEAK_OFFSET };
	rPos = { centerPos.x + CENTER_OFFSET, centerPos.y + CENTER_OFFSET };
	
}

bool HurtBlock::Update()
{
	if (GetDist(centerPos, playerRef->GetCenter()) >= MIN_ACTIVATION_DIST)
	{
		return false;
	}
	return CollisionCheck();
}

bool HurtBlock::CollisionCheck()
{
	Vector2 pp1 = playerRef->pos;
	Vector2 pp2 = {pp1.x + 1.f, pp1.y};
	Vector2 pp3 = { pp1.x + 1.f, pp1.y + 1.f};
	Vector2 pp4 = { pp1.x, pp1.y + 1.f };

	Vector2* collpos = nullptr;

	if (CheckCollisionLines(lPos, mPos, pp1, pp2, collpos) 
		|| CheckCollisionLines(lPos, mPos, pp2, pp3, collpos) 
		|| CheckCollisionLines(lPos, mPos, pp3, pp4, collpos) 
		|| CheckCollisionLines(lPos, mPos, pp4, pp1, collpos))
	{
		return true;
	}
	if (CheckCollisionLines(rPos, mPos, pp1, pp2, collpos)
		|| CheckCollisionLines(rPos, mPos, pp2, pp3, collpos)
		|| CheckCollisionLines(rPos, mPos, pp3, pp4, collpos)
		|| CheckCollisionLines(rPos, mPos, pp4, pp1, collpos))
	{
		return true;
	}

	
	return false;
}



void HurtBlock::Render()
{
	float size = 64.f;
	DrawLine(static_cast<int>(lPos.x * size), static_cast<int>(lPos.y * size), static_cast<int>(mPos.x * size), static_cast<int>(mPos.y * size), YELLOW);
	DrawLine(static_cast<int>(rPos.x * size), static_cast<int>(rPos.y * size), static_cast<int>(mPos.x * size), static_cast<int>(mPos.y * size), YELLOW);
}


float HurtBlock::GetDist(Vector2 vec1, Vector2 vec2)
{
	float x = vec1.x - vec2.x;
	float y = vec1.y - vec2.y;

	return sqrtf(x*x +y*y);
}
