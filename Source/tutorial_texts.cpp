#include "tutorial_texts.h"


void Tutorial::SetPlayerRef(Entity& ref)
{
	playerRef = &ref;
}
void Tutorial::Setup(Vector2 pos, int index)
{
	textPos[index] = pos;
}
void Tutorial::Render()
{
	float tut1Dist = GetDist(playerRef->pos, textPos[0]);
	float tut2Dist = GetDist(playerRef->pos, textPos[1]);
	float tut3Dist = GetDist(playerRef->pos, textPos[2]);

	float range = 5.f;
	if (tut1Dist < range)
	{
		txtRend.RenderText("'A and D' for Movement", static_cast<int>(textPos[0].x * config.tileSize), static_cast<int>(textPos[0].y * config.tileSize), FONT_SIZE, WHITE, BLACK);

		txtRend.RenderText("'Space' to Jump", static_cast<int>(textPos[0].x * config.tileSize), static_cast<int>(textPos[0].y * config.tileSize + FONT_SIZE), FONT_SIZE, WHITE, BLACK);

	}
	else if (tut2Dist < range)
	{
		txtRend.RenderText("'O' for Ordinary Attacks", static_cast<int>(textPos[1].x * config.tileSize), static_cast<int>(textPos[1].y * config.tileSize), FONT_SIZE, WHITE, BLACK);


		txtRend.RenderText("'P' to Parry", static_cast<int>(textPos[1].x * config.tileSize), static_cast<int>(textPos[1].y * config.tileSize + FONT_SIZE), FONT_SIZE, WHITE, BLACK);

	}
	else if (tut3Dist < range)
	{
		txtRend.RenderText("Press 'E' to claim a nearby Checkpoint", static_cast<int>(textPos[2].x * config.tileSize), static_cast<int>(textPos[2].y * config.tileSize), FONT_SIZE, WHITE, BLACK);

	}
}

float Tutorial::GetDist(Vector2 pos1, Vector2 pos2)
{
	float x = pos1.x - pos2.x;
	float y = pos1.y - pos2.y;
	return sqrtf((x * x) + (y * y));
}