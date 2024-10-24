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

	std::string time = " ";

	float timeSpent = 0.f;

	int hitCounter = 0;
	int deathCounter = 0;
public:
	ScoreManager();

	void AddHit() { hitCounter++; }
	void AddDeath() { deathCounter++; }
	void UpdateTimeKeeper(float dt); 
	std::string FilterTime(int value);

	void RenderTimeKeeper(); // Always
	void RenderStats(); // Last level
};