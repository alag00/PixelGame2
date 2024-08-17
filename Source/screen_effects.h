#pragma once
#include "raylib.h"

enum EFFECT_TYPE
{
	NONE = 0,
	FADE_TO_BLACK = 1,
	FADE_FROM_BLACK = 2,
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
public:
	void Setup(Camera2D& camRef, int screenWidth, int screenHeight);
	bool IsActive() { return isActive; }
	void Update(float dt);
	void Render();
	void StartEffect(EFFECT_TYPE newEffect);
};