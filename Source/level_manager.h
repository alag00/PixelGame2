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
#include "text_render.h"

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

	
	std::string sLevel;
	int nLevelWidth;
	int nLevelHeight;

	
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

	Vector2 tutorialPos1 = { 0.f,0.f };
	Vector2 tutorialPos2 = { 0.f,0.f };
	Vector2 tutorialPos3 = { 0.f,0.f };


	MiscManager miscManager;
	bool bossDefeated = false;

	bool exitLevel = false;

	SCENE_TYPE nextScene = SCENE_TYPE::NONE;
	bool isCutscening = false;
	CutsceneManager cutsceneManager;
	bool cutscenePlayed = false;

	bool levelDarkMode = false;
	float darkProgress = 0.f; 
	TextRenderer txtRend;
public:
	~LevelManager();
	SCENE_TYPE GetNewScene() override { return nextScene; }
	void LoadScene();
	void LeaveScene();
	bool Update();
	void Render();
	void RenderUI();
	void RenderBackground();
	void UpdateCam(float dt);

	void LevelSetup();
	void LevelRender();
	void RenderTutorial();
	char GetTile(int x, int y);
	void SetTile(int x, int y, char c);
	char GetTile(float x, float y);
	void SetTile(float x, float y, char c);

	void CollisionCheck(float dt);

	void AdjustPlayer(float dt);
	bool IsPlayerTouchBlockTile(char tileTypeOne, char tileTypeTwo);
	void CheckEvent();
	

	void RenderHpBars();
	float GetDist(Vector2 vec1, Vector2 vec2);
	void RenderCredit();
	void RenderDarkMode();

	void SetupTile(int x, int y);
	void RenderTile(int x, int y, Rectangle dst);

	void StartBoss();
};