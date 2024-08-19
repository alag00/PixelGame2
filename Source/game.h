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

enum Events
{
	None,
	NextLevel,
	Die,
};
class Game
{
private:
	Config config;
	int screenWidth = 1080;
	int screenHeight = 760;

	
	std::string sLevel;
	int nLevelWidth;
	int nLevelHeight;

	
	Player player;

	
	float fCameraPosX = 0.0f;
	float fCameraPosY = 0.0f;

	Camera2D cam{};
	Levels levels;

	int currentLevel = 1;

	Effect filter;

	Vector2 currentCheckPoint{ 0.f,0.f };
	Events currentEvent = None;

	Music caveMusic{};
	Music plainMusic{};
	Music castleMusic{};
	Music bossMusic{};

	Music currentSong{};

	Texture2D tileTextures{};

	
	EnemyManager enemyManager;
	
	Background background;

	Vector2 tutorialPos1 = { 0.f,0.f };
	Vector2 tutorialPos2 = { 0.f,0.f };
	Vector2 tutorialPos3 = { 0.f,0.f };

	//std::vector<CheckPoint> checkPointList{};
	//Sound checkPointSound{};
	MiscManager miscManager;
	bool bossDefeated = false;

public:
	~Game();
	void Run();
	void Update();
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
};