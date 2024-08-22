#pragma once
#include <string>

class Levels
{
private: 
	std::string currentLevel;
	int currentLevelWidth = 0;
	int currentevelHeight = 0;
	char bossChar = ' ';
	int cutsceneID = 0;
public:
	std::string GetLevel() { return currentLevel; }
	int GetLevelWidth() { return currentLevelWidth; }
	int GetLevelHeight() { return currentevelHeight; }
	char GetBossChar() { return bossChar; }
	int GetCutsceneID() { return cutsceneID; }

	void CreateLevelOne();
	void CreateLevelTwo();
	void CreateLevelThree();
	void CreateLevelFour();
	void CreateLevelFive();
};