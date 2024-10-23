#include "score_manager.h"

ScoreManager::ScoreManager()
{
	width = GetScreenWidth();
	height = GetScreenHeight();
}

void ScoreManager::UpdateTimeKeeper(float dt)
{
	timeSpent += dt;
	int min = (int)(timeSpent / 60.f);
	int sec = (int)timeSpent - min * 60;
	int dec = (int)((timeSpent - (float)(int)timeSpent) * 100.f);

	time = "Time: ";
	time += FilterTime(min) + ":";
	time += FilterTime(sec) + ":";
	time += FilterTime(dec);
}

std::string ScoreManager::FilterTime(int value)
{
	return (value < 10) ? "0" + std::to_string(value) : std::to_string(value);
}

void ScoreManager::RenderTimeKeeper()
{
	
	txtRend.RenderText(time, width - margin * 3, 10, fontSize, frontCol, backCol);
}

void ScoreManager::RenderStats()
{
	txtRend.RenderText("Total Stats", margin, margin, fontSize + 10, frontCol, backCol);

	txtRend.RenderText(time, margin, margin + fontSize * 2, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Damaged: %i", hitCounter), margin, margin + fontSize * 3, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Killed: %i", deathCounter), margin, margin + fontSize * 4, fontSize, frontCol, backCol);
}
