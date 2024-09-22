#include "grappling_point.h"

void GrapplingPoint::Setup(Vector2 newPos, Entity& ref)
{
	pos = { newPos.x + OFFSET_TO_CENTER, newPos.y + OFFSET_TO_CENTER };
	playerRef = &ref;
}
void GrapplingPoint::Update()
{
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
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

	DrawText("'Q'", (int)pos.x * (int)config.tileSize + OFFSET_X_TEXT, (int)pos.y * (int)config.tileSize + (int)config.tileSize, FONT_SIZE, WHITE);

}