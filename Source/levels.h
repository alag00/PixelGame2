#pragma once
#include <string>
#include "raylib.h"
#include "particle_manager.h"

class Levels
{
private: 
	std::string currentLevel;
	int currentLevelWidth = 0;
	int currentevelHeight = 0;
	char bossChar = ' ';
	int cutsceneID = 0;
	char spawnChar = ' ';

	Music currentSong{};
	Music songList[3];
	Music cutsceneSong{};
	Music currentBossSong{};
	Music bossSongList[2];

	Texture2D currentBackgrounds[3]{};
	Texture2D backgroundTxrs[5][3]{};

	Texture2D currentTileTxr{};
	Texture2D tileTextures[4];
	bool darkMode = false;
	bool startCutscene = false;

	ParticleManager* particleRef = nullptr;
public:
	void Load();
	void Unload();
	std::string GetLevel() { return currentLevel; }
	int GetLevelWidth() { return currentLevelWidth; }
	int GetLevelHeight() { return currentevelHeight; }
	char GetBossChar() { return bossChar; }
	char GetSpawnChar() { return spawnChar; }
	int GetCutsceneID() { return cutsceneID; }
	Music GetLevelSong() { return currentSong; }
	Music GetBossSong() { return currentBossSong; }
	Music GetCutsceneSong() { return cutsceneSong; }
	Texture2D GetLevelTexture() { return currentTileTxr; }
	bool GetLevelDarkMode() { return darkMode; }
	Texture2D* GetBackgroundTextures() { return currentBackgrounds; }
	bool GetStartCutscene() { return startCutscene; }
	void SetCurrentBackground(int index);
	void SetParticleRef(ParticleManager& ref) { particleRef = &ref; }
	void QueueLevelParticles(int level);


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
	void CreateLevelEleven();
	void CreateLevelTwelve();
	void CreateLevelThirteen();
	void CreateLevelFourteen();
	void CreateLevelFifteen();
};