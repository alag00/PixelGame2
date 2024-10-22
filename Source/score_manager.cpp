#include "score_manager.h"

ScoreManager::ScoreManager()
{
	width = GetScreenWidth();
	height = GetScreenHeight();
}

void ScoreManager::RenderTimeKeeper()
{
	// top right corner

	int min = (int)(timeSpent / 60.f);
	int sec = (int)timeSpent - min * 60;
	int dec = (int)((timeSpent - (float)(int)timeSpent)*10.f);
	std::string time = "Time: " + std::to_string(min) + ":" + std::to_string(sec) + ":" + std::to_string(dec);
	txtRend.RenderText(time, width - margin * 3, 10, fontSize, frontCol, backCol);
}

void ScoreManager::RenderStats()
{
	txtRend.RenderText("Total Stats", margin, margin, fontSize + 10, frontCol, backCol);

	int min = (int)(timeSpent / 60.f);
	int sec = (int)timeSpent - min * 60;
	int dec = (int)((timeSpent - (float)(int)timeSpent) * 10.f);
	std::string time = "Total Time: " + std::to_string(min) + ":" + std::to_string(sec) + ":" + std::to_string(dec);
	txtRend.RenderText(time, margin, margin + fontSize * 2, fontSize, frontCol, backCol);
	//txtRend.RenderText(TextFormat("Total Enemies Killed: %i", killsCounter), margin, margin + fontSize * 3, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Damaged: %i", hitCounter), margin, margin + fontSize * 3, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Killed: %i", deathCounter), margin, margin + fontSize * 4, fontSize, frontCol, backCol);
}
