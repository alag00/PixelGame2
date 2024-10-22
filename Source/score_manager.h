#pragma once
#include "text_render.h"

class ScoreManager
{
private:
	int width = 0;
	int height = 0;

	TextRenderer txtRend;
	int fontSize = 20;
	Color frontCol = WHITE;
	Color backCol = BLACK;
	int margin = 50;

	const int MAX_ENEMIES = 10;

	float timeSpent = 0.f;

	int killsCounter = 0;
	int hitCounter = 0;
	int deathCounter = 0;
public:
	ScoreManager();
	void AddKill() { killsCounter++; }
	void AddHit() { hitCounter++; }
	void AddDeath() { deathCounter++; }
	void UpdateTimeKeeper(float dt) { timeSpent += dt; } // When player can move -lastlevel

	void RenderTimeKeeper(); // Always
	void RenderStats(); // Last level
};