#include "level_manager.h"

LevelManager::~LevelManager()
{
	LeaveScene();
}

void LevelManager::LoadScene()
{
	
	background.SetSize(screenWidth, screenHeight);
	
	player.Setup();
	enemyManager.LoadEnemyAssets();
	enemyManager.GetPlayerRef(player);
	miscManager.Setup(player);
	levels.Load();
	levels.SetParticleRef(particleManager);
	tutorial.SetPlayerRef(player);
	darkMode.Setup(player, screenWidth, screenHeight);

	cam.offset = { screenWidth / 2.f, screenHeight / 2.f };
	cam.target = { screenWidth / 2.f, screenHeight / 2.f };
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	filter.Setup(cam, screenWidth, screenHeight);
	particleManager.SetCameraRef(cam);

	

	currentLevelSong = currentSong;
	PlayMusicStream(currentSong);

	cutsceneManager.Setup(cameraTargetPos, filter);

	LevelSetup();

	//particleManager.QueueParticle(FALLING_SNOW);
	
}

void LevelManager::LeaveScene()
{


	player.Unload();
	enemyManager.Unload();
	miscManager.Unload();
	background.Unload();
	levels.Unload();

	enemyManager.ClearEnemyList();
}

bool LevelManager::Update()
{
	UpdateMusicStream(currentSong);
	float dt = GetFrameTime();
	if (dt > DELTA_FAILSAFE_LIMIT)
	{
		return exitLevel;
	}
	particleManager.Update(dt);
	filter.Update(dt);
	if (currentEvent != None && currentEvent != ScreenShake)
	{
		CheckEvent();
		return exitLevel;
	}
	if (isCutscening)
	{
		if (cutsceneManager.Update(dt))
		{
			
			cutscenePlayed = true;
			filter.StartEffect(FADE_TO_BLACK);
			currentEvent = EndCutscene;
			
		}
		return exitLevel;
	}
	background.Update(cameraTargetPos, dt);
	
	UpdateEntities(dt);
	UpdateMiscs(dt);

	float percent = (float)player.health / (float)player.maxHealth;
	if (percent <= 0.f)
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.health = 1;
		player.Die();
	}

	
	if (levelDarkMode)
	{
		darkMode.Update(dt);
	}
	return exitLevel;
}

void LevelManager::UpdateEntities(float dt)
{

	if (IsKeyPressed(KEY_I))
	{
		particleManager.QueueParticle(SWORD_CLASH, player.GetCenter());
	}

	player.Update(dt);
	AdjustPlayer(dt);

	if (enemyManager.Update() && !bossDefeated)
	{
		bossDefeated = true;
		currentSong = currentLevelSong;
		PlayMusicStream(currentSong);
		for (int i = 0; i < miscManager.GetBarrierList().size(); i++)
		{
			Vector2 pos = miscManager.GetBarrierList().at(i);
			SetTile(pos.x, pos.y, L'.');
		}
	}
	for (int i = 0; i < enemyManager.GetEnemyList().size(); i++)
	{
		if (!enemyManager.GetEnemyList().at(i)->IsAlive())
		{
			continue;
		}
		enemyManager.GetEnemyList().at(i)->Update(dt);
		if (player.IsInAttackMode())
		{
			if (player.CollisionCheck(*enemyManager.GetEnemyList().at(i)))
			{
				currentEvent = HitFreeze;
				filter.StartEffect(HIT_FREEZE);
			}
		}
	}
}

void LevelManager::UpdateMiscs(float dt)
{
	int returnValue = miscManager.UpdateCheckPoints();
	if (returnValue != MISC_FAIL_CODE)
	{
		Vector2 tilePos = miscManager.GetCheckPointList().at(returnValue).GetPos();
		SetTile(tilePos.x, tilePos.y, L'?');
		currentCheckPoint = tilePos;
	}

	returnValue = miscManager.UpdateGrapplingPoints();
	if (returnValue != MISC_FAIL_CODE)
	{
		player.EnterGrapplingHookMode(miscManager.GetGrapPointList().at(returnValue).GetPos());
	}
	for (int i = 0; i < miscManager.GetGrapPointList().size(); i++)
	{
		if (miscManager.GetGrapPointList().at(i).GetIdeal())
		{
			Vector2 pos = miscManager.GetGrapPointList().at(i).GetPos();
			SetTile(pos.x, pos.y, L'R');
		}
		else
		{
			Vector2 pos = miscManager.GetGrapPointList().at(i).GetPos();
			SetTile(pos.x, pos.y, L'G');
		}
	}
	miscManager.UpdateDartTrapsPoints(dt);
	if (miscManager.UpdateHurtBlocks())
	{
		currentEvent = ScreenShake;
		filter.StartEffect(SCREEN_SHAKE);
		//filter.StartEffect(FADE_TO_BLACK);
		//currentEvent = Die;
		//player.Die();
		/*
		if (player.TakeTickDamage())
		{
			//currentEvent = HitFreeze;
			//filter.StartEffect(HIT_FREEZE);
			currentEvent = ScreenShake;
			filter.StartEffect(SCREEN_SHAKE);
		}
		*/
	}
}

void LevelManager::CheckEvent()
{
	if (filter.IsActive())
	{
		return;
	}
	switch (currentEvent)
	{
	case NextLevel:
		currentLevel++;
		LevelSetup();
		break;
	case Die:
		filter.StartEffect(FADE_FROM_BLACK);
		player.SetPosition(currentCheckPoint.x, currentCheckPoint.y);
		player.Respawn();
		enemyManager.Reset();
		enemyManager.SetBossActive(false);
		currentSong = currentLevelSong;
		PlayMusicStream(currentSong);
		for (int i = 0; i < miscManager.GetBarrierList().size(); i++)
		{
			Vector2 pos = miscManager.GetBarrierList().at(i);
			SetTile(pos.x, pos.y, L'.');
		}
		
		break;
	case ScreenShake:
		cam.rotation = 0.f;
		break;
	case CloseGame:
		nextScene = SCENE_TYPE::MAIN_MENU;
		exitLevel = true;
		break;
	case StartCutscene:
		isCutscening = true;
		filter.StartEffect(FADE_FROM_BLACK);
		currentSong = currentCutsceneSong;
		PlayMusicStream(currentSong);
		break;
	case EndCutscene:
		filter.StartEffect(FADE_FROM_BLACK);
		isCutscening = false;
		if (levels.GetCutsceneID() < 0)
		{
			StartBoss();
			break;
		}
		currentSong = currentLevelSong;
		PlayMusicStream(currentSong);
		break;
	}

	currentEvent = None;
}

void LevelManager::AdjustPlayer(float dt)
{




	// Calculate potential new position
	float newPlayerPosX = player.GetPosition().x + player.GetVelocity().x * dt;
	float newPlayerPosY = player.GetPosition().y + player.GetVelocity().y * dt;

	
	// Check for Collision
	if (player.GetVelocity().x < 0) 
	{
		if (CheckMovingPlayer(newPlayerPosX, player.GetPosition().y, 0.f, 0.f, 0.f, 0.9f))
		{
			newPlayerPosX = static_cast<float>((int)newPlayerPosX + 1);
			player.SetVelocity(0.f, player.GetVelocity().y);
		}
		/*
		char tileTypeOne = GetTile(newPlayerPosX + 0.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(newPlayerPosX + 0.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				newPlayerPosX = static_cast<float>((int)newPlayerPosX + 1);
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}
		*/
	}
	else if (player.GetVelocity().x > 0)
	{
		if (CheckMovingPlayer(newPlayerPosX, player.GetPosition().y, 1.f, 0.f, 1.f, 0.9f))
		{
			newPlayerPosX = static_cast<float>((int)newPlayerPosX);
			player.SetVelocity(0.f, player.GetVelocity().y);
		}
		/*
		char tileTypeOne = GetTile(newPlayerPosX + 1.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(newPlayerPosX + 1.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				newPlayerPosX = static_cast<float>((int)newPlayerPosX);
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}
		*/

	}

	player.SetOnGround(false);
	if (player.GetVelocity().y < 0) 
	{
		if (CheckMovingPlayer(newPlayerPosX, newPlayerPosY, 0.f, 0.f, 0.9f, 0.f))
		{
			newPlayerPosY = static_cast<float>((int)newPlayerPosY + 1);
			player.SetVelocity(player.GetVelocity().x, 0.f);
		}

		/*
		char tileTypeOne = GetTile(newPlayerPosX + 0.0f, newPlayerPosY);
		char tileTypeTwo = GetTile(newPlayerPosX + 0.9f, newPlayerPosY);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				newPlayerPosY = static_cast<float>((int)newPlayerPosY + 1);
				player.SetVelocity(player.GetVelocity().x, 0.f);
			}
		}
	*/
	}
	else if (player.GetVelocity().y > 0) 
	{
		if (CheckMovingPlayer(newPlayerPosX, newPlayerPosY, 0.f, 1.f, 0.9f, 1.f))
		{
			newPlayerPosY = static_cast<float>((int)newPlayerPosY);
			player.SetVelocity(player.GetVelocity().x, 0.f);
			player.SetOnGround(true);
		}

		/*
		char tileTypeOne = GetTile(newPlayerPosX + 0.0f, newPlayerPosY + 1.0f);
		char tileTypeTwo = GetTile(newPlayerPosX + 0.9f, newPlayerPosY + 1.0f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				newPlayerPosY = static_cast<float>((int)newPlayerPosY);
				player.SetVelocity(player.GetVelocity().x, 0.f);
				player.SetOnGround(true);
			}
		}
		*/
	
	}
	//newPlayerPosX = std::clamp(newPlayerPosX, 0.f, (float)levelWidth);
	//newPlayerPosY = std::clamp(newPlayerPosY, 0.f, (float)levelHeight);

	if (newPlayerPosX < 0.f)
	{
		newPlayerPosX = 0.f;
		player.SetVelocity(0.f, player.GetVelocity().y);
	}
	if (newPlayerPosX > (float)levelWidth)
	{
		newPlayerPosX = (float)levelWidth;
		player.SetVelocity(0.f, player.GetVelocity().y);
	}
	if (newPlayerPosY < 0.f)
	{
		newPlayerPosY = 0.f;
		player.SetVelocity(player.GetVelocity().x, 0.f);
	}
	if (newPlayerPosY > (float)levelHeight)
	{
		newPlayerPosY = (float)levelHeight;
		player.SetVelocity(player.GetVelocity().x, 0.f);
	}
	
	player.SetPosition(newPlayerPosX, newPlayerPosY);

	
	float camOffset = 0.f;

	cameraTargetPos.x = player.GetCenter().x;
	cameraTargetPos.y = player.GetCenter().y - camOffset;

	
	
	

}

bool LevelManager::CheckMovingPlayer(float playerPosX, float playerPosY, float t1Xoffset, float t1Yoffset, float t2Xoffset, float t2Yoffset)
{
	Vector2 t1 = { playerPosX + t1Xoffset, playerPosY + t1Yoffset };
	Vector2 t2 = { playerPosX + t2Xoffset, playerPosY + t2Yoffset };

	char tileTypeOne = GetTile(t1.x, t1.y);
	char tileTypeTwo = GetTile(t2.x, t2.y);
	
	if (tileTypeOne == L'D' || tileTypeTwo == L'D' || tileTypeOne == L'H' || tileTypeTwo == L'H')
	{
		if (tileTypeOne == L'D' || tileTypeOne == L'H')
		{
			miscManager.ActivateHurtBlockAt((int)t1.x, (int)t1.y);
		}
		if (tileTypeTwo == L'D' || tileTypeTwo == L'H')
		{
			miscManager.ActivateHurtBlockAt((int)t2.x, (int)t2.y);
		}
		return false;
	}
	
	if (tileTypeOne != L'.' || tileTypeTwo != L'.')
	{
		if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
		{
			return true;
		}
	}
	return false;
}
/*
void LevelManager::CheckDeathBlock(Vector2 playerPos, Vector2 tilePos)
{
	/*
	float offset = 0.1f;
	Rectangle tileBox = {tilePos.x + offset, tilePos.y + offset, 1.f - offset * 2.f, 1.f };
	
	//Rectangle tileBox = { tilePos.x , tilePos.y , 1.f , 1.f};
	Rectangle playerBox = { playerPos.x, playerPos.y, 1.f, 1.f };
	if (CheckCollisionRecs(tileBox, playerBox))
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.Die();
	}
	
	Vector2 lpos = { tilePos.x, tilePos.y + 1.f };
	Vector2 mpos = { tilePos.x + 1.f, tilePos.y};
	//Vector2 rpos = { tilePos.x , tilePos.y + 1.f };

	Rectangle playerBox = {playerPos.x, playerPos.y, 1.f, 1.f};
	if (LineBoxCollisionCheck(lpos, mpos, playerBox))// || LineBoxCollisionCheck(rpos, mpos, playerBox))
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.Die();
	}
	
	Vector2 center = { tilePos.x + 0.5f, tilePos.y + 1.f };
	Rectangle playerBox = { playerPos.x, playerPos.y, 1.f, 1.f };
	if (CheckCollisionCircleRec(center, 0.5f, playerBox))// || LineBoxCollisionCheck(rpos, mpos, playerBox))
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.Die();
	}
}

bool LevelManager::LineBoxCollisionCheck(Vector2 l1, Vector2 l2, Rectangle box)
{
	Vector2 boxMin = {box.x, box.y}; // Top-left corner
	Vector2 boxMax = { box.x + box.width, box.y + box.height }; // Bottom-right corner

	float tmin = (boxMin.x - l1.x) / (l2.x - l1.x);
	float tmax = (boxMax.x - l1.x) / (l2.x - l1.x);

	if (tmin > tmax) std::swap(tmin, tmax);

	float tymin = (boxMin.y - l1.y) / (l2.y - l1.y);
	float tymax = (boxMax.y - l1.y) / (l2.y - l1.y);

	if (tymin > tymax) std::swap(tymin, tymax);

	// Check for overlap in both x and y axis
	if ((tmin > tymax) || (tymin > tmax)) return false;

	tmin = std::max(tmin, tymin);
	tmax = std::min(tmax, tymax);

	// If tmax < 0, the line is completely outside of the AABB
	if (tmax < 0) return false;

	return true;
}
*/
bool LevelManager::IsPlayerTouchBlockTile(char tileTypeOne, char tileTypeTwo)
{
	if (tileTypeOne == L'#' || tileTypeTwo == L'#')
	{
		// Brick
		return true;
	}
	if (tileTypeOne == L'x' || tileTypeTwo == L'x')
	{
		// Brick 2
		return true;
	}
	if (tileTypeOne == L'%' || tileTypeTwo == L'%')
	{
		// Grass
		return true;
	}
	if (tileTypeOne == L'_' || tileTypeTwo == L'_')
	{
		// Dirt
		return true;
	}
	if (tileTypeOne == L'*' || tileTypeTwo == L'*')
	{
		// Stone
		return true;
	}
	if (tileTypeOne == L'o' || tileTypeTwo == L'o')
	{
		// Stone2
		return true;
	}
	if (tileTypeOne == L'w' || tileTypeTwo == L'w')
	{
		// wood
		return true;
	}
	if (tileTypeOne == L'=' || tileTypeTwo == L'=')
	{
		// BARRIER
		return true;
	}
	if (tileTypeOne == L's' || tileTypeTwo == L's')
	{
		// entrance block
		return true;
	}
	if (tileTypeOne == L'i' || tileTypeTwo == L'i')
	{
		// invisible block
		return true;
	}
	if (tileTypeOne == L'L' || tileTypeTwo == L'L')
	{
		// climb block
		player.EnterClimbMode();
		return true;
	}
	if (tileTypeOne == L'B' || tileTypeTwo == L'B')
	{
		if (bossDefeated)
		{
			return false;
		}
		StartBoss();
		return false;
	}
	if (tileTypeOne == L'V' || tileTypeTwo == L'V')
	{
		if (cutscenePlayed)
		{
			return false;
		}
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = StartCutscene;
		return false;
	}
	
	if (tileTypeOne == L'C' || tileTypeTwo == L'C')
	{
		
		return false;
	}
	if (tileTypeOne == L'G' || tileTypeTwo == L'G')
	{

		
		return false;
	}
	if (tileTypeOne == L'R' || tileTypeTwo == L'R')
	{

		
		return false;
	}
	/*
	if (tileTypeOne == L'H' || tileTypeTwo == L'H')
	{


		return false;
	}
	if (tileTypeOne == L'D' || tileTypeTwo == L'D')
	{
		return false;
	}
	*/
	if (tileTypeOne == L'+' || tileTypeTwo == L'+')
	{
		// Next Level
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = NextLevel;

		return false;
	}
	if (tileTypeOne == L'-' || tileTypeTwo == L'-')
	{
		// Brick Background
		return false;
	}
	if (tileTypeOne == L'y' || tileTypeTwo == L'y')
	{
		// Brick Background 2
		return false;
	}

	if (tileTypeOne == L',' || tileTypeTwo == L',')
	{
		// Stone Background
		return false;
	}
	if (tileTypeOne == L'c' || tileTypeTwo == L'c')
	{
		// Stone Background
		return false;
	}
	if (tileTypeOne == L'd' || tileTypeTwo == L'd')
	{
		// Dirt Background
		return false;
	}
	if (tileTypeOne == L':' || tileTypeTwo == L':')
	{
		// wood Background
		return false;
	}
	if (tileTypeOne == L'{' || tileTypeTwo == L'{')
	{
		// GraveStone 1
		return false;
	}
	if (tileTypeOne == L'}' || tileTypeTwo == L'}')
	{
		// GraveStone 2
		return false;
	}
	if (tileTypeOne == L'[' || tileTypeTwo == L'[')
	{
		// GraveStone 3
		return false;
	}
	if (tileTypeOne == L']' || tileTypeTwo == L']')
	{
		// GraveStone 4
		return false;
	}
	if (tileTypeOne == L'?' || tileTypeTwo == L'?')
	{
		// GraveStone 4
		return false;
	}
	if (tileTypeOne == L'E' || tileTypeTwo == L'E')
	{
		// Init Close Game
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = CloseGame;
		return false;
	}
	return true;
}

void LevelManager::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	background.Render();
	BeginMode2D(cam);

	LevelRender();
	miscManager.Render();
	if (isCutscening)
	{
		cutsceneManager.Render();
		particleManager.Render();
		EndMode2D();
		cutsceneManager.RenderUI();
		filter.Render();
		EndDrawing();
		return;
	}

	enemyManager.Render();
	player.Render();
	enemyManager.RenderUI();
	if (currentLevel == 1)
	{
		tutorial.Render();
	}
	particleManager.Render();
	EndMode2D();
	if (levelDarkMode)
	{
		darkMode.Render();
	}
	
	RenderHpBars();
	if (currentLevel == CURRENT_LAST_LEVEL)
	{
		RenderCredit();
	}
	
	filter.Render();
	EndDrawing();
}

void LevelManager::LevelSetup()
{
	particleManager.ClearList();
	levels.CreateLevel(currentLevel);
	currentSong = levels.GetLevelSong();
	PlayMusicStream(currentSong);
	currentLevelSong = currentSong;
	currentBossSong = levels.GetBossSong();
	currentCutsceneSong = levels.GetCutsceneSong();
	currentTileTextures = levels.GetLevelTexture();
	cutsceneManager.SwitchCutscene(levels.GetCutsceneID());

	levelString = levels.GetLevel();
	levelWidth = levels.GetLevelWidth();
	levelHeight = levels.GetLevelHeight();
	levelDarkMode = levels.GetLevelDarkMode();
	
	background.SetLevelBackground(levels.GetBackgroundTextures());
	

	filter.StartEffect(FADE_FROM_BLACK);
	enemyManager.ClearEnemyList();

	miscManager.ClearLists();
	bossDefeated = false;
	cutscenePlayed = false;
	

	
	//std::vector<Vector2> enemyPos{};

	for (int y = 0; y < levelHeight; y++)
	{
		for (int x = 0; x < levelWidth; x++)
		{
			SetupTile(x, y);
		}
	}
	
}

void LevelManager::LevelRender()
{
	
	int tileWidth = (int)config.tileSize;
	int tileHeight = (int)config.tileSize;
	int visibleTilesX = screenWidth / tileWidth;
	int visibleTilesY = screenHeight / tileHeight;



	cam.target = { cameraTargetPos.x * tileWidth, cameraTargetPos.y * tileHeight };

	float halfWidth = screenWidth / 2.f;
	float halfHeight = screenHeight / 2.f;
	
	if (cam.target.x < halfWidth) cam.target.x = halfWidth;
	if (cam.target.y < halfHeight) cam.target.y = halfHeight;
	if (cam.target.x > (tileWidth * levelWidth) - halfWidth) cam.target.x = (tileWidth * levelWidth) - halfWidth;
	if (cam.target.y > (tileHeight * levelHeight) - halfHeight) cam.target.y = (tileHeight * levelHeight) - halfHeight;

	cameraTargetPos.x = cam.target.x / tileWidth;
	cameraTargetPos.y = cam.target.y / tileHeight;


	
	Rectangle dst{ 0.f, 0.f,0.f,0.f };

	for (int y = static_cast<int>((cameraTargetPos.y - (visibleTilesY / 2.f) - 2)) ; y < (cameraTargetPos.y) +(visibleTilesY / 2.f) +1 ; y++)
	{
		for (int x = static_cast<int>((cameraTargetPos.x - (visibleTilesX / 2.f) - 2)) ; x < (cameraTargetPos.x) +(visibleTilesX / 2.f) + 1  ; x++)
		{
			dst = { (float)x * tileWidth,(float)y * tileHeight,(float)tileWidth, (float)tileHeight };
			RenderTile(x, y, dst);
			
		}
	}

	//Color pCol = YELLOW;
	//pCol.a = 40;
	//DrawRectangle(static_cast<int>(player.pos.x * tileWidth), static_cast<int>(player.pos.y * tileHeight), tileWidth, tileHeight, pCol);


}

char LevelManager::GetTile(int x, int y)
{
	if (x >= 0 && x < levelWidth && y >= 0 && y < levelHeight)
	{
		int index = y * levelWidth + x;
		return levelString[index];
	}
	return ' ';
}

void LevelManager::SetTile(int x, int y, char c)
{
	if (x >= 0 && x < levelWidth && y >= 0 && y < levelHeight)
	{
		int index = y * levelWidth + x;
		levelString[index] = c;
	}
}

char LevelManager::GetTile(float x, float y)
{
	
	return GetTile((int)x,(int)y);
}

void LevelManager::SetTile(float x, float y, char c)
{
	SetTile((int)x, (int)y, c);
}

void LevelManager::RenderHpBars()
{
	if (currentEvent != NextLevel && currentEvent != Die)
	{
		float margin = 3.f;
		Rectangle bar{ 64.f - margin, (float)screenHeight , 200.f + margin * 2.f,  48.f + margin * 2.f };
		bar.y -= bar.x + bar.height;
		DrawRectangleRec(bar, GREEN);

		bar = { 64.f, (float)screenHeight, 200.f, 48.f };
		bar.y -= bar.x + bar.height;
		DrawRectangleRec(bar, BLACK);

		margin = 4.f;
		Rectangle remainingHealth = { bar.x + margin, bar.y + margin, bar.width - margin * 2.f, bar.height - margin * 2.f };
		float percent = (float)player.health / (float)player.maxHealth;
		remainingHealth.width *= percent;

		DrawRectangleRec(remainingHealth, GREEN);

	}
	enemyManager.RenderBossBar();

}

void LevelManager::RenderCredit()
{
	DrawText("Thank you for playing!", 100, screenHeight / 2, 40, YELLOW);
}

void LevelManager::SetupTile(int x, int y)
{
	if (GetTile(x, y) == L'C')
	{
		miscManager.CreateCheckPoint(x, y);
		return;
	}
	if (GetTile(x, y) == L'S')
	{
		currentCheckPoint = { (float)x, (float)y };
		player.SetPosition((float)x, (float)y);
		SetTile(x, y, levels.GetSpawnChar());
		return;
	}
	if (GetTile(x, y) == L'K')
	{
		bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
		enemyManager.CreateKnight(Vector2((float)x, (float)y), isBoss);
		SetTile(x, y, L'.');

		return;
	}
	if (GetTile(x, y) == L'Z')
	{

		bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
		enemyManager.CreateSkeleton(Vector2((float)x, (float)y), isBoss);
		SetTile(x, y, L'.');

		return;
	}
	if (GetTile(x, y) == L'N')
	{
		bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
		enemyManager.CreateNecromancer(Vector2((float)x, (float)y), isBoss);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'P')
	{
		bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
		enemyManager.CreatePyromancer(Vector2((float)x, (float)y), isBoss);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'W')
	{
		enemyManager.CreateWeepingAngel(Vector2((float)x, (float)y));
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'p')
	{
		bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
		enemyManager.CreatePumpkin(Vector2((float)x, (float)y), isBoss);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'U')
	{
		enemyManager.CreateGhost(Vector2((float)x, (float)y));
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'=')
	{
		miscManager.CreateBarrierPoint(Vector2((float)x, (float)y));
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'G')
	{
		miscManager.CreateGrapplingPoint(x, y);
		return;
	}
	if (GetTile(x, y) == L'l')
	{
		miscManager.CreateDartTrapPoint(x, y, true);
		SetTile(x, y, L'T');
		return;
	}
	if (GetTile(x, y) == L'r')
	{
		miscManager.CreateDartTrapPoint(x, y, false);
		SetTile(x, y, L'T');
		return;
	}
	if (GetTile(x, y) == L'H')
	{
		miscManager.CreateHurtBlock(x, y, false);
		return;
	}
	if (GetTile(x, y) == L'D')
	{
		miscManager.CreateHurtBlock(x, y, true);
		return;
	}
	if (GetTile(x, y) == L'v')
	{
		miscManager.CreateObject(x, y, currentLevel, 0);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'b')
	{
		miscManager.CreateObject(x, y, currentLevel, 1);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'n')
	{
		miscManager.CreateObject(x, y, currentLevel, 2);
		SetTile(x, y, L'.');
		return;
	}
	if (currentLevel != 1)
	{
		return;
	}
	if (GetTile(x, y) == L'1')
	{
		tutorial.Setup(Vector2((float)x, (float)y), 0);
		//tutorialPos1 = Vector2((float)x, (float)y);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'2')
	{
		tutorial.Setup(Vector2((float)x, (float)y), 1);
		//tutorialPos2 = Vector2((float)x, (float)y);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'3')
	{
		tutorial.Setup(Vector2((float)x, (float)y), 2);
		//tutorialPos3 = Vector2((float)x, (float)y);
		SetTile(x, y, L'.');
		return;
	}
}

void LevelManager::RenderTile(int x, int y, Rectangle dst)
{
	Rectangle src{ 0.f,0.f,16.f,16.f };
	Vector2 origin{ 0.f,0.f };

	wchar_t sTileID = GetTile(x, y);
	switch (sTileID)
	{
	case L'.': // Sky
	case L'B': // Activate Boss
	case L'V': // Activate Cutscene
		return;
	case L'#':// Brick
		src = { 0.f,0.f, 16.f, 16.f };
		break;
	case L'x':// Brick2
		src = { 0.f,32.f, 16.f, 16.f };
		break;
	case L'-': // Brick Wall
		src = { 0.f,16.f, 16.f, 16.f };
		break;
	case L'y': // Brick Wall 2
		src = { 0.f,48.f, 16.f, 16.f };
		break;
	case L'*': // Stone
		src = { 16.f,0.f, 16.f, 16.f };
		break;
	case L'o': // Stone 2
		src = { 16.f,32.f, 16.f, 16.f };
		break;
	case L',': // Stone Wall
		src = { 16.f,16.f, 16.f, 16.f };
		break;
	case L'c': // Stone Wall 2
		src = { 16.f,48.f, 16.f, 16.f };
		break;
	case L'_': // Dirt
		src = { 32.f,16.f, 16.f, 16.f };
		break;
	case L'%': // Grass Dirt
		src = { 32.f,0.f, 16.f, 16.f };
		break;
	case L'd': // Dirt Wall
		src = { 32.f,32.f, 16.f, 16.f };
		break;
	case L'w': // Wood 1
		src = { 48.f, 0.f, 16.f, 16.f };
		break;
	case L':': // Wood wall
		src = { 48.f, 16.f, 16.f, 16.f };
		break;
	case L'L': // Climb Block
		src = { 80.f,0.f, 16.f, 16.f };
		break;
	case L'=': // Barrier Block
		src = { 80.f,16.f, 16.f, 16.f };
		break;
	case L'H': // Hurt Block
		src = { 64.f,16.f, 16.f, 16.f };
		break;
	case L'D': // Death Block
		src = { 64.f,0.f, 16.f, 16.f };
		break;
	case L'C': // CheckPoint Unclaimed
		src = { 96.f,0.f, 16.f, 16.f };
		break;
	case L'?': // CheckPoint Claimed
		src = { 96.f,16.f, 16.f, 16.f };
		break;
	case L'G': // Grappling Point
		src = { 96.f,32.f, 16.f, 16.f };
		break;
	case L'R': // Valid Grappling Point
		src = { 96.f,48.f, 16.f, 16.f };
		break;
	case L'T': // Dart Trap
		src = { 64.f,32.f, 16.f, 16.f };
		break;
	case L'{': // Misc 1
		src = { 112.f,0.f, 16.f, 16.f };
		break;
	case L'}': // Misc 2
		src = { 112.f,16.f, 16.f, 16.f };
		break;
	case L'[': // Misc 3
		src = { 112.f, 32.f, 16.f, 16.f };
		break;
	case L']': // Misc 4
		src = { 112.f, 48.f, 16.f, 16.f };
		break;

	default:
		DrawRectangleRec(dst, BLACK);
		return;
	}
	DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
}

void LevelManager::StartBoss()
{
	for (int i = 0; i < miscManager.GetBarrierList().size(); i++)
	{
		Vector2 pos = miscManager.GetBarrierList().at(i);
		SetTile(pos.x, pos.y, L'=');
	}
	enemyManager.SetBossActive(true);
	currentSong = currentBossSong;
	PlayMusicStream(currentSong);
}
