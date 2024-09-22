#include "dark_mode.h"


void DarkMode::Setup(Entity& ref, int width, int height)
{
	playerRef = &ref;
	screenWidth = (float)width;
	screenHeight = (float)height;

	halfWidth = screenWidth / 2.f;
	barThickness = screenHeight / 5.f;
}

void DarkMode::Update(float dt)
{
	darkProgress += (playerRef->GetLookSide()) ? -SPEED * dt : SPEED * dt;
	darkProgress = (darkProgress > 1.f) ? 1.f : darkProgress;
	darkProgress = (darkProgress < 0.f) ? 0.f : darkProgress;

	leftDark = { 0.f, 0.f, halfWidth, screenHeight };
	rightDark = { halfWidth, 0.f, halfWidth, screenHeight };
	topBar = { 0.f, 0.f, screenWidth, barThickness };
	botBar = { 0.f, screenHeight - barThickness , screenWidth, barThickness };
}

void DarkMode::Render()
{
	leftDark.x = std::lerp(-config.tileSize, -halfWidth + barThickness, darkProgress);
	rightDark.x = std::lerp(screenWidth - barThickness, halfWidth + config.tileSize, darkProgress);

	DrawRectangleRec(leftDark, BLACK);
	DrawRectangleRec(rightDark, BLACK);
	DrawRectangleRec(topBar, BLACK);
	DrawRectangleRec(botBar, BLACK);
}