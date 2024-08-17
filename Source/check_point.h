#pragma once
#include "raylib.h"

class CheckPoint
{
private:
	float dist = 0.f;
	bool activated = false;
public:

	void Update(float dt);
	void Render();
	void RenderUI();
};