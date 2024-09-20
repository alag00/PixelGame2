#include "check_point.h"


void CheckPoint::Setup(Vector2 newPos, Entity& ref)
{
	pos = newPos;
	playerRef = &ref;
}

bool CheckPoint::Update()
{
	float x = (pos.x + offsetToCenter) - playerRef->GetCenter().x;
	float y = (pos.y + offsetToCenter) - playerRef->GetCenter().y;
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

	
	txtRend.RenderText("'E'", static_cast<int>((pos.x + textOffset) * config.tileSize), static_cast<int>((pos.y - textOffset) * config.tileSize), textSize, WHITE, BLACK);

}
