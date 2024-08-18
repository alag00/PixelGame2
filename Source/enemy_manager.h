#pragma once
#include "entity.h"
#include "enemy.h"
#include "enemy_knight.h"
#include "enemy_skeleton.h"
#include "enemy_necromancer.h"
#include <vector>

class EnemyManager
{
private:
	Texture2D skeletonTextures[4];
	Texture2D knightTextures[6];
	Texture2D necromancerTextures[7];

	std::vector<Enemy*> enemyList{};
	Entity* playerRef = nullptr;
	Enemy* bossRef = nullptr;

	bool isBossActive = false;
public:
	void Unload();
	void SetBossActive(bool newValue) { isBossActive = newValue; }
	void ClearEnemyList();
	void Reset();
	std::vector<Enemy*> GetEnemyList();
	void LoadEnemyTextures();
	void GetPlayerRef(Entity& ref);
	void CreateSkeleton(Vector2 pos, bool isBoss);
	void CreateKnight(Vector2 pos, bool isBoss);
	void CreateNecromancer(Vector2 pos, bool isBoss);

	void Render();
	void RenderUI();
	void RenderBossBar();
	void Update();
};