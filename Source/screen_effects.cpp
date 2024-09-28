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
		color.a = (progress > midPointFade) ? alphaRange : static_cast<char>(alphaRange * progress);
		break;
	case FADE_FROM_BLACK:
		color.a = (progress > midPointFade) ? 0 : static_cast<char>(alphaRange - (alphaRange * progress));
		break;
	case SCREEN_SHAKE:
		camera->rotation += progress * magnitude;
		magnitude = -magnitude;
		return;
	case HIT_FREEZE:
		return;
	}

	//DrawRectangle(static_cast<int>(camera->target.x - camera->offset.x), static_cast<int>(camera->target.y - camera->offset.y), width, height, color);
	DrawRectangle(0, 0, width, height, color);
}
void Effect::Update(float dt)
{
	if (!isActive)
	{
		return;
	}
	progress += dt;
	if (progress > duration)
	{
		camera->rotation = 0.f;
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
	switch (newEffect)
	{
	case FADE_FROM_BLACK:
	case FADE_TO_BLACK:
		duration = screenFadeDuration;
		break;
	case SCREEN_SHAKE:
		duration = screenShakeDuration;
		break;
	case HIT_FREEZE:
		duration = screenFreezeDuration;
		break;
	}
}
