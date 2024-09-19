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

	UnloadSound(initAttackSound);
	UnloadSound(swingAttackSound);
	UnloadSound(deathSound);

	for (int i = 0; i < 10; i++)
	{
		UnloadTexture(pyromancerP1Textures[i]);
		UnloadTexture(pyromancerP2Textures[i]);
	}
	UnloadTexture(pyromancerP2Textures[10]);
	UnloadTexture(weepingAngelTxr);
	for (int i = 0; i < 6; i++)
	{
		UnloadTexture(pumpkinTextures[i]);
	}
}

void EnemyManager::SetBossActive(bool newValue)
{
	 isBossActive = newValue; 
	 if (bossRef != nullptr)
	 {
		 bossRef->active = newValue;
	 }
}

void EnemyManager::LoadEnemyAssets()
{
	
	skeletonTextures[0] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyIdleAtlas.png");
	skeletonTextures[1] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeathAtlas.png");
	skeletonTextures[2] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyAttackAtlas.png");
	skeletonTextures[3] = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeflectAtlas.png");

	knightTextures[0] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyIdleAtlas.png");
	knightTextures[1] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyWalkAtlas.png");
	knightTextures[2] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyAttackAtlas.png");
	knightTextures[3] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyAttack2Atlas.png");
	knightTextures[4] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyThrustAtlas.png");
	knightTextures[5] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyDeflectAtlas.png");
	knightTextures[6] = LoadTexture("Assets/EnemyTextures/KnightEnemy/KnightEnemyDeathAtlas.png");

	necromancerTextures[0] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	necromancerTextures[1] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyDeathAtlas.png");
	necromancerTextures[2] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyMeleeAttackAtlas.png");
	necromancerTextures[3] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyRangedAttackAtlas.png");
	necromancerTextures[4] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyDeflectAtlas.png");
	necromancerTextures[5] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyPushAtlas.png");

	necromancerTextures[6] = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyProjectileAtlas.png");


	pyromancerP1Textures[0] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobIdleAtlas.png");
	pyromancerP1Textures[1] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobWalkAtlas.png");
	pyromancerP1Textures[2] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobRefillAtlas.png");
	pyromancerP1Textures[3] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobBlockOneAtlas.png");
	pyromancerP1Textures[4] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobBlockTwoAtlas.png");
	pyromancerP1Textures[5] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobOilAttackAtlas.png");
	pyromancerP1Textures[6] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobSeathAttackAtlas.png");
	pyromancerP1Textures[7] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobSliceAttackAtlas.png");
	pyromancerP1Textures[8] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobThrustAttackAtlas.png");
	pyromancerP1Textures[9] = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobTransformationAtlas.png");

	pyromancerP2Textures[0] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerIdleAtlas.png");
	pyromancerP2Textures[1] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerRunAtlas.png");
	pyromancerP2Textures[2] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerBlockAtlas.png");
	pyromancerP2Textures[3] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerSliceAtlas.png");
	pyromancerP2Textures[4] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerThrustAtlas.png");

	pyromancerP2Textures[5] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerDeployWingsAtlas.png");
	pyromancerP2Textures[6] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerFlyAtlas.png");
	pyromancerP2Textures[7] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerRangedAttackAtlas.png");
	pyromancerP2Textures[8] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerFireProjectileAtlas.png");
	pyromancerP2Textures[9] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerFlyAttackAtlas.png");
	pyromancerP2Textures[10] = LoadTexture("Assets/EnemyTextures/Gnob/SecondPhase/PyromancerDeathAtlas.png");

	weepingAngelTxr = LoadTexture("Assets/EnemyTextures/WeepingAngel/WeepingAngelAtlas.png");

	pumpkinTextures[0] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinIdleAtlas.png");
	pumpkinTextures[1] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinWalkAtlas.png");
	pumpkinTextures[2] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinInitSpinAtlas.png");
	pumpkinTextures[3] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinSpinAtlas.png");
	pumpkinTextures[4] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinHurtAtlas.png");
	pumpkinTextures[5] = LoadTexture("Assets/EnemyTextures/Pumpokin/PumpokinDeathAtlas.png");

	
	initAttackSound = LoadSound("Assets/Audio/SFX/EnemyAttackInit.mp3");
	swingAttackSound = LoadSound("Assets/Audio/SFX/EnemySwing.mp3");
	deathSound = LoadSound("Assets/Audio/SFX/EnemyDeath.mp3");
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
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
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
	newEnemy->SetTextures(knightTextures);
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
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
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
	newEnemy->Setup();
	if (isBoss)
	{
		bossRef = newEnemy;
		newEnemy->isBoss = true;
		newEnemy->active = false;
	}
	enemyList.push_back(newEnemy);
}

void EnemyManager::CreatePyromancer(Vector2 pos, bool isBoss)
{
	PyromancerEnemy* newEnemy = new PyromancerEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(pyromancerP1Textures, pyromancerP2Textures);
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
	newEnemy->Setup();
	if (isBoss)
	{
		bossRef = newEnemy;
		newEnemy->isBoss = true;
		newEnemy->active = false;
	}
	enemyList.push_back(newEnemy);
}

void EnemyManager::CreateWeepingAngel(Vector2 pos)
{
	WeepingAngelEnemy* newEnemy = new WeepingAngelEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(weepingAngelTxr);
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
	newEnemy->Setup();
	
	enemyList.push_back(newEnemy);
}

void EnemyManager::CreatePumpkin(Vector2 pos, bool isBoss)
{
	PumpkinEnemy* newEnemy = new PumpkinEnemy();
	newEnemy->SetPlayerRef(*playerRef);
	newEnemy->SetStartPos(pos);
	newEnemy->SetTextures(pumpkinTextures);
	newEnemy->SetAudio(deathSound, initAttackSound, swingAttackSound);
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
		float margin = 3.f;
		Rectangle bar{ GetScreenWidth() / 2.f - margin,  GetScreenHeight() - 64.f  , 500.f + margin * 2.f, 48.f + margin  * 2.f};
		bar.y -= bar.height - margin;
		DrawRectangleRec(bar, RED);

		

		bar = { GetScreenWidth() / 2.f,  GetScreenHeight() - 64.f , 500.f, 48.f};
		bar.y -= bar.height;
		DrawRectangleRec(bar, BLACK);

		margin = 4.f;
		Rectangle remainingHealth = { bar.x + margin, bar.y + margin, bar.width - margin * 2.f, bar.height - margin * 2.f };
		float percent = (float)bossRef->health / (float)bossRef->maxHealth;
		remainingHealth.width *= percent;

		DrawRectangleRec(remainingHealth, RED);
	}
}
bool EnemyManager::Update()
{
	if (bossRef != nullptr && !bossRef->IsAlive())
	{
		isBossActive = false;
		return true;
	}
	return false;

}