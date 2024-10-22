#include "score_manager.h"

ScoreManager::ScoreManager()
{
	width = GetScreenWidth();
	height = GetScreenHeight();
}

void ScoreManager::RenderTimeKeeper()
{
	// top right corner
	txtRend.RenderText(TextFormat("Time: %f", timeSpent), width - margin * 3, 0, fontSize, frontCol, backCol);
}

void ScoreManager::RenderStats()
{
	txtRend.RenderText("Total Stats", margin, margin, fontSize + 10, frontCol, backCol);

	txtRend.RenderText(TextFormat("Total Time Spent: %f", timeSpent), margin, margin + fontSize * 2, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Enemies Killed: %i", killsCounter), margin, margin + fontSize * 3, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Hit: %i", hitCounter), margin, margin + fontSize * 4, fontSize, frontCol, backCol);
	txtRend.RenderText(TextFormat("Total Times Killed: %i", deathCounter), margin, margin + fontSize * 5, fontSize, frontCol, backCol);
}
