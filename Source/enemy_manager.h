#pragma once
#include "entity.h"
#include "enemy.h"
#include "enemy_knight.h"
#include "enemy_skeleton.h"
#include "enemy_necromancer.h"
#include "enemy_pyromancer.h"
#include "enemy_statue.h"
#include "enemy_pumpkin.h"
#include "enemy_ghost.h"
#include "enemy_guardian.h"
#include <vector>

class EnemyManager
{
private:
	Texture2D skeletonTextures[4];
	Texture2D knightTextures[7];
	Texture2D necromancerTextures[7];
	Texture2D pyromancerP1Textures[10];
	Texture2D pyromancerP2Textures[11];
	Texture2D weepingAngelTxr;
	Texture2D pumpkinTextures[6];
	Texture2D ghostTextures{};
	Texture2D guardianTextures[6];

	Sound initAttackSound{};
	Sound swingAttackSound{};
	Sound deathSound{};

	std::vector<Enemy*> enemyList{};
	Entity* playerRef = nullptr;
	Enemy* bossRef = nullptr;

	bool isBossActive = false;
public:
	void Unload();
	void SetBossActive(bool newValue);
	void ClearEnemyList();
	void Reset();
	std::vector<Enemy*> GetEnemyList();
	void LoadEnemyAssets();
	void GetPlayerRef(Entity& ref);
	void CreateSkeleton(Vector2 pos, bool isBoss);
	void CreateKnight(Vector2 pos, bool isBoss);
	void CreateNecromancer(Vector2 pos, bool isBoss);
	void CreatePyromancer(Vector2 pos, bool isBoss);
	void CreateWeepingAngel(Vector2 pos);
	void CreatePumpkin(Vector2 pos, bool isBoss);
	void CreateGhost(Vector2 pos);
	void CreateGuardian(Vector2 pos, bool isBoss);

	void Render();
	void RenderUI();
	void RenderBossBar();
	bool Update();
};