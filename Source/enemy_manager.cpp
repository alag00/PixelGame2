#include "enemy_manager.h"

void EnemyManager::ClearEnemyList()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		delete enemyList.at(i);
		enemyList.at(i) = nullptr;
	}
	enemyList.clear();

	bossRef = nullptr;
}
void EnemyManager::Reset()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList.at(i)->Reset();

	}
}
std::vector<Enemy*> EnemyManager::GetEnemyList()
{
	return enemyList;
}

void EnemyManager::Unload()
{
	for (int i = 0; i < 6; i++)
	{
		if (i < 4)
		{
			UnloadTexture(skeletonTextures[i]);
		}
		UnloadTexture(knightTextures[i]);
		UnloadTexture(necromancerTextures[i]);
	}
	UnloadTexture(necromancerTextures[6]);
}

void EnemyManager::LoadEnemyTextures()
{
	skeletonTextures[0] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyIdleAtlas.png");
	skeletonTextures[1] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeathAtlas.png");
	skeletonTextures[2] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyAttackAtlas.png");
	skeletonTextures[3] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeflectAtlas.png");

	knightTextures[0] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyIdleAtlas.png");
	knightTextures[1] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyDeathAtlas.png");
	knightTextures[2] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyWalkAtlas.png");
	knightTextures[3] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyAttackAtlas.png");
	knightTextures[4] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyAttack2Atlas.png");
	knightTextures[5] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyDeflectAtlas.png");

	necromancerTextures[0] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	necromancerTextures[1] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyDeathAtlas.png");
	necromancerTextures[2] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyMeleeAttackAtlas.png");
	necromancerTextures[3] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyRangedAttackAtlas.png");
	necromancerTextures[4] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyDeflectAtlas.png");
	necromancerTextures[5] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyPushAtlas.png");

	necromancerTextures[6] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyProjectileAtlas.png");

}
void EnemyManager::GetPlayerRef(Entity& ref)
{
	playerRef = &ref;
}


void EnemyManager::CreateSkeleton(Vector2 pos, bool isBoss)
{
	SkeletonEnemy* newEnemy = new SkeletonEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(skeletonTextures[0], skeletonTextures[1], skeletonTextures[2], skeletonTextures[3]);
	newEnemy->Setup();
	if (isBoss)
	{
		bossRef = newEnemy;
		newEnemy->isBoss = true;
	}
	enemyList.push_back(newEnemy);
}
void EnemyManager::CreateKnight(Vector2 pos, bool isBoss)
{
	KnightEnemy* newEnemy = new KnightEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(knightTextures[0], knightTextures[1], knightTextures[2], knightTextures[3], knightTextures[4], knightTextures[5]);
	newEnemy->Setup();
	if (isBoss)
	{
		bossRef = newEnemy;
		newEnemy->isBoss = true;
	}
	enemyList.push_back(newEnemy);
}
void EnemyManager::CreateNecromancer(Vector2 pos, bool isBoss)
{
	NecromancerEnemy* newEnemy = new NecromancerEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(necromancerTextures[0], necromancerTextures[1], necromancerTextures[2], necromancerTextures[3], necromancerTextures[4], necromancerTextures[5], necromancerTextures[6]);
	newEnemy->Setup();
	if (isBoss)
	{
		bossRef = newEnemy;
		newEnemy->isBoss = true;
	}
	enemyList.push_back(newEnemy);
}

void EnemyManager::Render()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList.at(i)->Render();
	}
}
void EnemyManager::RenderUI()
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList.at(i)->IsAlive())
		{
			continue;
		}
		enemyList.at(i)->RenderUI();
	}
}

void EnemyManager::RenderBossBar()
{
	if (isBossActive)
	{
		Rectangle blackBar{ GetScreenWidth() / 2.f,  GetScreenHeight() - 68.f , 500.f, 48.f};
		DrawRectangleRec(blackBar, BLACK);

		float margin = 5.f;
		Rectangle remainingHealth = { blackBar.x + margin, blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f };
		float percent = (float)bossRef->health / (float)bossRef->maxHealth;
		remainingHealth.width *= percent;

		DrawRectangleRec(remainingHealth, RED);
	}
}
void EnemyManager::Update()
{
	if (bossRef != nullptr && !bossRef->IsAlive())
	{
		isBossActive = false;
	}


}