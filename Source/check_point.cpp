#include "check_point.h"


void CheckPoint::Setup(Vector2 newPos, Entity& ref)
{
	pos = newPos;
	playerRef = &ref;
}

bool CheckPoint::Update()
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
	DrawText("Press 'E'", static_cast<int>(pos.x * config.tileSize), static_cast<int>(pos.y * config.tileSize), 20, YELLOW);
}
