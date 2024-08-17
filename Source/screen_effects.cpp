#include "screen_effects.h"

void Effect::Render()
{
	if (!isActive)
	{
		return;
	}
	Color color = BLACK;
	switch (currentEffect)
	{
	case FADE_TO_BLACK:
		color.a = (progress > 1.f) ? 255 : 255 * progress;
		break;
	case FADE_FROM_BLACK:
		color.a = (progress > 1.f) ? 0 : 255 - (255 * progress);
		break;
	}

	DrawRectangle(camera->target.x - camera->offset.x, camera->target.y - camera->offset.y, width, height, color);
}
void Effect::Update(float dt)
{
	if (!isActive)
	{
		return;
	}
	progress += dt;
	if (progress > 2.0f)
	{
		isActive = false;
	}
}
void Effect::Setup(Camera2D& camRef, int screenWidth, int screenHeight)
{
	camera = &camRef;
	width = screenWidth;
	height = screenHeight;
}

void Effect::StartEffect(EFFECT_TYPE newEffect)
{
	currentEffect = newEffect;
	isActive = true;
	progress = 0.f;
}
