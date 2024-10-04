#pragma once
#include "raylib.h"

enum EFFECT_TYPE
{
	NONE = 0,
	FADE_TO_BLACK = 1,
	FADE_FROM_BLACK = 2,
	SCREEN_SHAKE = 3,
	HIT_FREEZE = 4,
};
class Effect
{
private:
	EFFECT_TYPE currentEffect = NONE;
	bool isActive = false;
	float progress = 0.f;
	int width = 0;
	int height = 0;
	Camera2D* camera = nullptr;
	float magnitude = 10.f;
	float duration = 2.f;
	const float screenFadeDuration = 2.f;
	const float screenShakeDuration = 0.2f;
	const float screenFreezeDuration = 0.1f;
	const float midPointFade = 1.f;
	const unsigned char alphaRange = 255;
public:
	void Setup(Camera2D& camRef, int screenWidth, int screenHeight);
	bool IsActive() { return isActive; }
	void Update(float dt);
	void Render();
	void StartEffect(EFFECT_TYPE newEffect);
	void CustomDuration(float newValue) { duration = newValue; }
};