#pragma once
#include <string>
#include "raylib.h"

class Levels
{
private: 
	std::string currentLevel;
	int currentLevelWidth = 0;
	int currentevelHeight = 0;
	char bossChar = ' ';
	int cutsceneID = 0;

	Music currentSong{};
	Music songList[3];

	Texture2D currentBackgrounds[3]{};
	Texture2D backgroundTxrs[5][3]{};

	Texture2D currentTileTxr{};
	Texture2D tileTextures[2];
	bool darkMode = false;
public:
	void Load();
	void Unload();
	std::string GetLevel() { return currentLevel; }
	int GetLevelWidth() { return currentLevelWidth; }
	int GetLevelHeight() { return currentevelHeight; }
	char GetBossChar() { return bossChar; }
	int GetCutsceneID() { return cutsceneID; }
	Music GetLevelSong() { return currentSong; }
	Texture2D GetLevelTexture() { return currentTileTxr; }
	bool GetLevelDarkMode() { return darkMode; }
	Texture2D* GetBackgroundTextures() { return currentBackgrounds; }
	void SetCurrentBackground(int index);

	void CreateLevel(int level);

	void CreateLevelOne();
	void CreateLevelTwo();
	void CreateLevelThree();
	void CreateLevelFour();
	void CreateLevelFive();

	void CreateLevelSix();
	void CreateLevelSeven();
	void CreateLevelEight();
	void CreateLevelNine();
	void CreateLevelTen();
};