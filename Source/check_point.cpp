#include "check_point.h"


void CheckPoint::Setup(Vector2 newPos, Entity& ref)
{
	pos = newPos;
	playerRef = &ref;
}

bool CheckPoint::Update(float dt)
{
	float x = (pos.x + 0.5f) - playerRef->GetCenter().x;
	float y = (pos.y + 0.5f) - playerRef->GetCenter().y;
	dist =  sqrtf((x * x) + (y * y));

	inRange = false;
	if (dist < range)
	{
		inRange = true;
	}
	if (inRange && IsKeyPressed(KEY_E))
	{
		activated = true;
		return true;
	}
	return false;
}

void CheckPoint::Render()
{
	if (!inRange)
	{
		return;
	}
	DrawText("Press 'E'", pos.x * 64.f, pos.y * 64.f, 20, YELLOW);
}
