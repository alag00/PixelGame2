#pragma once
#include "raylib.h"
#include "player.h"
#include <vector>
#include "enemy.h"
#include <string>
#include "levels.h"
#include "screen_effects.h"
#include "background.h"

#include "enemy_manager.h"
#include "misc_manager.h"
#include "config.h"
#include "scene.h"
#include "cutscene_manager.h"
#include <cmath>
//#include <algorithm>
#include "tutorial_texts.h"
#include "dark_mode.h"
#include "particle_manager.h"
#include "credits.h"

enum Events
{
	None,
	NextLevel,
	Die,
	ScreenShake,
	HitFreeze,
	CloseGame,
	StartCutscene,
	EndCutscene,
};
class LevelManager : public Scene
{
private:
	Config config;
	int screenWidth = 1920;
	int screenHeight = 1080;

	
	std::string levelString;
	int levelWidth;
	int levelHeight;

	
	Player player;

	Vector2 cameraTargetPos{ 0.f,0.f };


	Camera2D cam{};
	Levels levels;

	int currentLevel = 9;

	Effect filter;

	Vector2 currentCheckPoint{ 0.f,0.f };
	Events currentEvent = None;


	Music currentBossSong{};
	Music currentCutsceneSong{};
	Music currentLevelSong{};
	Music currentSong{};

	Texture2D currentTileTextures{};

	
	EnemyManager enemyManager;
	
	Background background;

	Tutorial tutorial;
	Credits credits;

	MiscManager miscManager;
	bool bossDefeated = false;

	bool exitLevel = false;

	SCENE_TYPE nextScene = SCENE_TYPE::NONE;
	bool isCutscening = false;
	CutsceneManager cutsceneManager;
	bool cutscenePlayed = false;

	DarkMode darkMode;
	bool levelDarkMode = false;
	
	const int CURRENT_LAST_LEVEL = 13;
	const int MISC_FAIL_CODE = 4444;
	const float DELTA_FAILSAFE_LIMIT = 0.1f;

	ParticleManager particleManager;
public:
	~LevelManager();
	SCENE_TYPE GetNewScene() override { return nextScene; }
	void LoadScene();
	void LeaveScene();

	bool Update();
	void UpdateEntities(float dt);
	void UpdateMiscs(float dt);
	void Render();
	
	void UpdateCam(float dt);

	void LevelSetup();
	void SetupTile(int x, int y);

	void LevelRender();
	void RenderTile(int x, int y, Rectangle dst);

	char GetTile(int x, int y);
	void SetTile(int x, int y, char c);
	char GetTile(float x, float y);
	void SetTile(float x, float y, char c);



	void AdjustPlayer(float dt);
	bool CheckMovingPlayer(float playerPosX, float playerPosY, float t1Xoffset, float t1Yoffset, float t2Xoffset, float t2Yoffset);
	//void CheckDeathBlock(Vector2 playerPos, Vector2 tilePos);
	//bool LineBoxCollisionCheck(Vector2 l1, Vector2 l2, Rectangle box);
	bool IsPlayerTouchBlockTile(char tileTypeOne, char tileTypeTwo);
	void CheckEvent();
	

	void RenderHpBars();
	
	//void RenderCredit();



	void StartBoss();
};