#include "grappling_point.h"

void GrapplingPoint::Setup(Vector2 newPos, Entity& ref)
{
	pos = { newPos.x + 0.5f, newPos.y + 0.5f };
	playerRef = &ref;
}
void GrapplingPoint::Update()
{
	float x = (pos.x + 0.0f) - playerRef->GetCenter().x;
	float y = (pos.y + 0.0f) - playerRef->GetCenter().y;
	dist = sqrtf((x * x) + (y * y));

	inRange = false;
	if (dist < range)
	{
		inRange = true;
	}
}
void GrapplingPoint::Render()
{
	
	if (!isIdeal)
	{
		return;
	}

	DrawText("'Q'", (int)pos.x * 64 + 16, (int)pos.y * 64 +64, 40, WHITE);

}