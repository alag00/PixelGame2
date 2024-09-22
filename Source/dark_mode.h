#pragma once
#include "raylib.h"
#include "entity.h"
#include <cmath>
#include "config.h"

class DarkMode
{
private:
	Entity* playerRef = nullptr;
	float darkProgress = 0.f;
	float screenWidth = 0.f;
	float screenHeight = 0.f;
	float halfWidth = 0.f;
	float barThickness = 0.f;
	const float SPEED = 2.f;
	Config config;

	Rectangle leftDark = { 0.f, 0.f, 0.f, 0.f };
	Rectangle rightDark = { 0.f, 0.f, 0.f, 0.f };
	Rectangle topBar = { 0.f, 0.f, 0.f, 0.f };
	Rectangle botBar = { 0.f, 0.f, 0.f, 0.f };
public:
	void Setup(Entity& ref, int width, int height);
	void Update(float dt);
	void Render();
};