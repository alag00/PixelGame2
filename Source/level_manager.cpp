#include "level_manager.h"

LevelManager::~LevelManager()
{
	enemyManager.ClearEnemyList();
}
void LevelManager::LoadScene()
{
	/*
	//SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Unholy Trek");
	InitAudioDevice();
	SetTargetFPS(60);
	Image icon = LoadImage("Assets/Icon.png");
	SetWindowIcon(icon);
	UnloadImage(icon);
	*/

	/*
	mainMenu.Setup(screenWidth, screenHeight);
	while(mainMenu.Update())
	{
		mainMenu.Render();
	}
	mainMenu.Unload();
	*/
	background.SetSize(screenWidth, screenHeight);
	//background.Setup();
	player.Setup();
	enemyManager.LoadEnemyAssets();
	enemyManager.GetPlayerRef(player);
	miscManager.Setup(player);
	levels.Load();
	

	cam.offset = { screenWidth / 2.f, screenHeight / 2.f };
	cam.target = { screenWidth / 2.f, screenHeight / 2.f };
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	filter.Setup(cam, screenWidth, screenHeight);

	
	//tileTextures = LoadTexture("Assets/TileTextures/Textures.png");

	//bossMusic = LoadMusicStream("Assets/Audio/Music/BossTheme.mp3");
	/*
	caveMusic = LoadMusicStream("Assets/Audio/Music/CaveTheme.mp3");
	plainMusic = LoadMusicStream("Assets/Audio/Music/OminousSpook.mp3");
	castleMusic = LoadMusicStream("Assets/Audio/Music/MarchEcho.mp3");
	*/

	//checkPointSound = LoadSound("Assets/Audio/SFX/Hit.mp3");
	//currentSong = bossMusic;
	currentLevelSong = currentSong;
	PlayMusicStream(currentSong);

	cutsceneManager.Setup(cameraTargetPos);

	LevelSetup();
	/*
	while (!WindowShouldClose() && isRunning)
	{
		Update();
		Render();
	}
	*/
	/*
	UnloadTexture(tileTextures);

	player.Unload();
	enemyManager.Unload();
	miscManager.Unload();
	background.Unload();
	*/
	/*
	UnloadMusicStream(currentSong);
	UnloadMusicStream(currentLevelSong);
	UnloadMusicStream(bossMusic);
	UnloadMusicStream(caveMusic);
	UnloadMusicStream(plainMusic);
	UnloadMusicStream(castleMusic);
	*/
	//UnloadSound(checkPointSound);

	//CloseAudioDevice();
	//CloseWindow();
}
void LevelManager::LeaveScene()
{
	//UnloadTexture(tileTextures);

	player.Unload();
	enemyManager.Unload();
	miscManager.Unload();
	background.Unload();
	levels.Unload();
}
bool LevelManager::Update()
{
	UpdateMusicStream(currentSong);
	float dt = GetFrameTime();
	if (dt > 0.1f)
	{
		return exitLevel;
	}
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
			//isCutscening = false;
			cutscenePlayed = true;
			filter.StartEffect(FADE_TO_BLACK);
			currentEvent = EndCutscene;
			
		}
		return exitLevel;
	}
	background.Update(cameraTargetPos, dt);
	/*
	// Debug
	if (IsKeyPressed(KEY_T))
	{
		filter.StartEffect(SCREEN_SHAKE);
		currentEvent = ScreenShake;
	}
	*/
	CheckEvent();
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

	float percent = (float)player.health / (float)player.maxHealth;
	if (percent <= 0.f)
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.health = 1;
		player.Die();
	}

	int returnValue = miscManager.UpdateCheckPoints();
	if (returnValue != 4444)
	{
		Vector2 tilePos = miscManager.GetCheckPointList().at(returnValue).GetPos();
		SetTile(tilePos.x, tilePos.y, L'?');
		currentCheckPoint = tilePos;
	}

	returnValue = miscManager.UpdateGrapplingPoints();
	if (returnValue != 4444)
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
	if (levelDarkMode)
	{
		darkProgress += (player.GetLookSide()) ? -2.f * dt: 2.f * dt;
		darkProgress = (darkProgress > 1.f) ? 1.f : darkProgress;
		darkProgress = (darkProgress < 0.f) ? 0.f : darkProgress;
	}
	return exitLevel;
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
		break;
	case EndCutscene:
		filter.StartEffect(FADE_FROM_BLACK);
		isCutscening = false;
		if (levels.GetCutsceneID() > 0)
		{
			StartBoss();
		}
		// Stop Rendering Cutscene
		break;
	}

	currentEvent = None;
}

void LevelManager::AdjustPlayer(float dt)
{




	// Calculate potential new position
	float fNewPlayerPosX = player.GetPosition().x + player.GetVelocity().x * dt;
	float fNewPlayerPosY = player.GetPosition().y + player.GetVelocity().y * dt;

	
	// Check for Collision
	if (player.GetVelocity().x < 0) 
	{

		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosX = static_cast<float>((int)fNewPlayerPosX + 1);
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}
	}
	else if (player.GetVelocity().x > 0)
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosX = static_cast<float>((int)fNewPlayerPosX);
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}

	}

	player.SetOnGround(false);
	if (player.GetVelocity().y < 0) 
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosY = static_cast<float>((int)fNewPlayerPosY + 1);
				player.SetVelocity(player.GetVelocity().x, 0.f);
			}
		}
	
	}
	else if (player.GetVelocity().y > 0) 
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosY = static_cast<float>((int)fNewPlayerPosY);
				player.SetVelocity(player.GetVelocity().x, 0.f);
				player.SetOnGround(true);
			}
		}
	
	}

	
	player.SetPosition(fNewPlayerPosX, fNewPlayerPosY);

	//background.Update(player.GetVelocity(), dt);

	float camOffset = 0.f;

	cameraTargetPos.x = player.GetCenter().x;
	cameraTargetPos.y = player.GetCenter().y - camOffset;

	
	
	

}

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
	if (tileTypeOne == L'L' || tileTypeTwo == L'L')
	{
		// entrance block
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
		
		//currentCheckPoint = player.GetPosition();	
		return false;
	}
	if (tileTypeOne == L'G' || tileTypeTwo == L'G')
	{

		//currentCheckPoint = player.GetPosition();	
		return false;
	}
	if (tileTypeOne == L'R' || tileTypeTwo == L'R')
	{

		//currentCheckPoint = player.GetPosition();	
		return false;
	}
	if (tileTypeOne == L'D' || tileTypeTwo == L'D')
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		return false;
	}
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
	RenderBackground();
	BeginMode2D(cam);

	LevelRender();
	miscManager.Render();
	if (isCutscening)
	{
		cutsceneManager.Render();
		filter.Render();
		EndMode2D();
		cutsceneManager.RenderUI();
		EndDrawing();
		return;
	}

	enemyManager.Render();
	player.Render();
	RenderUI();
	if (currentLevel == 1)
	{
		RenderTutorial();
	}
	filter.Render();
	EndMode2D();
	if (levelDarkMode)
	{
		RenderDarkMode();
	}
	
	RenderHpBars();
	if (currentLevel == 10)
	{
		RenderCredit();
	}
	EndDrawing();
}

void LevelManager::RenderUI()
{
	//miscManager.Render();
	/*
	for (int i = 0; i < checkPointList.size(); i++)
	{
		checkPointList.at(i).Render();
	}
	*/
	enemyManager.RenderUI();
}

void LevelManager::RenderBackground()
{
	background.Render();
}

void LevelManager::LevelSetup()
{
	/*
	switch (currentLevel)
	{
	case 1:
		levels.CreateLevelOne();
		currentSong = caveMusic;
		PlayMusicStream(currentSong);
		break;
	case 2:
		levels.CreateLevelTwo();
		currentSong = plainMusic;
		PlayMusicStream(currentSong);
		break;
	case 3:
		levels.CreateLevelThree();
		currentSong = plainMusic;
		PlayMusicStream(currentSong);
		break;
	case 4:
		levels.CreateLevelFour();
		currentSong = castleMusic;
		PlayMusicStream(currentSong);
		break;
	case 5:
		levels.CreateLevelFive();
		currentSong = castleMusic;
		PlayMusicStream(currentSong);
		break;
	default:
		levels.CreateLevelOne();
		break;
	}
	*/
	levels.CreateLevel(currentLevel);
	currentSong = levels.GetLevelSong();
	PlayMusicStream(currentSong);
	currentLevelSong = currentSong;
	currentBossSong = levels.GetBossSong();
	currentTileTextures = levels.GetLevelTexture();
	cutsceneManager.SwitchCutscene(levels.GetCutsceneID());

	sLevel = levels.GetLevel();
	nLevelWidth = levels.GetLevelWidth();
	nLevelHeight = levels.GetLevelHeight();
	levelDarkMode = levels.GetLevelDarkMode();
	
	background.SetLevelBackground(levels.GetBackgroundTextures());
	//background.SetLevelBackground(currentLevel);

	filter.StartEffect(FADE_FROM_BLACK);
	enemyManager.ClearEnemyList();

	miscManager.ClearLists();
	bossDefeated = false;
	cutscenePlayed = false;
	//checkPointList.clear();

	//int totalEnemies = 0;
	std::vector<Vector2> enemyPos{};

	for (int y = 0; y < nLevelHeight; y++)
	{
		for (int x = 0; x < nLevelWidth; x++)
		{
			SetupTile(x, y);
		}
	}
	
}

void LevelManager::LevelRender()
{
	// Draw Level
	int nTileWidth = 64;
	int nTileHeight = 64;
	int nVisibleTilesX = screenWidth / nTileWidth;
	int nVisibleTilesY = screenHeight / nTileHeight;



	cam.target = { cameraTargetPos.x * nTileWidth, cameraTargetPos.y * nTileHeight };

	float halfWidth = screenWidth / 2.f;
	float halfHeight = screenHeight / 2.f;
	
	if (cam.target.x < halfWidth) cam.target.x = halfWidth;
	if (cam.target.y < halfHeight) cam.target.y = halfHeight;
	if (cam.target.x > (nTileWidth * nLevelWidth) - halfWidth) cam.target.x = (nTileWidth * nLevelWidth) - halfWidth;
	if (cam.target.y > (nTileHeight * nLevelHeight) - halfHeight) cam.target.y = (nTileHeight * nLevelHeight) - halfHeight;

	cameraTargetPos.x = cam.target.x / nTileWidth;
	cameraTargetPos.y = cam.target.y / nTileHeight;


	//Rectangle src{ 0.f,0.f, 16.f, 16.f };
	Rectangle dst{ 0.f, 0.f,0.f,0.f };
	//Vector2 origin = { 0.f,0.f };
	// Draw visible tile map
	for (int y = static_cast<int>((cameraTargetPos.y - (nVisibleTilesY / 2.f) - 2)) ; y < (cameraTargetPos.y) +(nVisibleTilesY / 2.f) +1 ; y++)
	{
		for (int x = static_cast<int>((cameraTargetPos.x - (nVisibleTilesX / 2.f) - 2)) ; x < (cameraTargetPos.x) +(nVisibleTilesX / 2.f) + 1  ; x++)
		{
			dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
			RenderTile(x, y, dst);
			/*
			wchar_t sTileID = GetTile(x, y);
			switch (sTileID)
			{
			case L'.': // Sky

				break;
			case L'#':// Brick
				 src = {0.f,0.f, 16.f, 16.f};
				 dst = { (float)x * nTileWidth,(float) y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'x':// Brick2
				src = { 0.f,32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'-': // Brick Wall
				src = { 0.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'y': // Brick Wall 2
				src = { 0.f,48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'*': // Stone
				src = { 16.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'o': // Stone 2
				src = { 16.f,32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L',': // Stone Wall
				src = { 16.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'c': // Stone Wall 2
				src = { 16.f,48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'_': // Dirt
				src = { 32.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'%': // Grass Dirt
				src = { 32.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'd': // Dirt Wall
				src = { 32.f,32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'L': // Climb Block
				src = { 80.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'=': // Barrier Block
				src = { 80.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'D': // Death Block
				src = { 80.f,32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'C': // CheckPoint Unclaimed
				src = { 96.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'?': // CheckPoint Claimed
				src = { 96.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'G': // Grappling Point
				src = { 96.f,32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'R': // Valid Grappling Point
				src = { 96.f,48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'T': // Dart Trap
				src = { 80.f,48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'B': // Activate Boss
				break;
			case L'V': // Activate Cutscene
				break;
			case L'{': // Misc 1
				src = { 112.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'}': // Misc 2
				src = { 112.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'[': // Misc 3
				src = { 112.f, 32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L']': // Misc 4
				src = { 112.f, 48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(currentTileTextures, src, dst, origin, 0.f, WHITE);
				break;
			
			default:
				DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, BLACK);
				break;
			}
			*/
		}
	}




}

void LevelManager::RenderTutorial()
{
	float tut1Dist = GetDist(player.pos, tutorialPos1);
	float tut2Dist = GetDist(player.pos, tutorialPos2);
	float tut3Dist = GetDist(player.pos, tutorialPos3);

	float range = 5.f;
	if (tut1Dist < range)
	{
		txtRend.RenderText("'A and D' for Movement", static_cast<int>(tutorialPos1.x * config.tileSize), static_cast<int>(tutorialPos1.y * config.tileSize), 30, WHITE, BLACK);
		/*
		DrawRectangle(static_cast<int>(tutorialPos1.x * config.tileSize), static_cast<int>(tutorialPos1.y * config.tileSize), 300, 75, BROWN);

		DrawText("'A and D' for Movement", static_cast<int>(tutorialPos1.x * config.tileSize), static_cast<int>(tutorialPos1.y * config.tileSize), 30, BLACK);
		DrawText("'A and D' for Movement", static_cast<int>(tutorialPos1.x * config.tileSize)-3, static_cast<int>(tutorialPos1.y * config.tileSize) -3 , 30, WHITE);
		*/
		txtRend.RenderText("'Space' to Jump", static_cast<int>(tutorialPos1.x * config.tileSize), static_cast<int>(tutorialPos1.y * config.tileSize + 30), 30, WHITE, BLACK);
		//DrawText("'Space' to Jump", static_cast<int>(tutorialPos1.x * config.tileSize), static_cast<int>(tutorialPos1.y * config.tileSize + 30), 30, BLACK);
		//DrawText("'Space' to Jump", static_cast<int>(tutorialPos1.x * config.tileSize) - 3, static_cast<int>(tutorialPos1.y * config.tileSize + 30) - 3, 30, WHITE);
	}
	else if (tut2Dist < range)
	{
		txtRend.RenderText("'O' for Ordinary Attacks", static_cast<int>(tutorialPos2.x * config.tileSize), static_cast<int>(tutorialPos2.y * config.tileSize), 30, WHITE, BLACK);
		//DrawText("'O' for Ordinary Attacks", static_cast<int>(tutorialPos2.x * config.tileSize), static_cast<int>(tutorialPos2.y * config.tileSize), 30, BLACK);
		//DrawText("'O' for Ordinary Attacks", static_cast<int>(tutorialPos2.x * config.tileSize)-3, static_cast<int>(tutorialPos2.y * config.tileSize)-3, 30, WHITE);

		txtRend.RenderText("'P' to Parry", static_cast<int>(tutorialPos2.x * config.tileSize), static_cast<int>(tutorialPos2.y * config.tileSize + 30), 30, WHITE, BLACK);
		//DrawText("'P' to Parry", static_cast<int>(tutorialPos2.x * config.tileSize), static_cast<int>(tutorialPos2.y * config.tileSize + 30), 30, BLACK);
		//DrawText("'P' to Parry", static_cast<int>(tutorialPos2.x * config.tileSize)-3, static_cast<int>(tutorialPos2.y * config.tileSize + 30)-3, 30, WHITE);
	}
	else if (tut3Dist < range)
	{
		txtRend.RenderText("Press 'E' to claim a nearby Checkpoint", static_cast<int>(tutorialPos3.x * config.tileSize), static_cast<int>(tutorialPos3.y * config.tileSize), 30, WHITE, BLACK);
		//DrawText("Press 'E' to claim nearby Checkpoints", static_cast<int>((tutorialPos3.x - 3) * config.tileSize), static_cast<int>(tutorialPos3.y * config.tileSize), 30, YELLOW);
	}
}

char LevelManager::GetTile(int x, int y)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
	{
		int index = y * nLevelWidth + x;
		return sLevel[index];
	}
	return ' ';
}

void LevelManager::SetTile(int x, int y, char c)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
	{
		int index = y * nLevelWidth + x;
		sLevel[index] = c;
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
		DrawRectangleRec(bar, YELLOW);

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

float LevelManager::GetDist(Vector2 vec1, Vector2 vec2)
{
	float x = vec1.x - vec2.x;
	float y = vec1.y - vec2.y;
	return sqrtf((x * x) + (y * y));
}

void LevelManager::RenderCredit()
{
	DrawText("Thank you for playing!", 100, screenHeight / 2, 40, YELLOW);
}

void LevelManager::RenderDarkMode() // -1.f to 1.f    left max to right max
{
	float halfWidth = (float)screenWidth / 2.f;

	Rectangle leftDark = {0.f, 0.f, halfWidth, (float)screenHeight};
	Rectangle rightDark = { halfWidth, 0.f, halfWidth, (float)screenHeight };

	float margin = (float)screenHeight / 5.f;
	Rectangle topBar = { 0.f, 0.f, (float)screenWidth, margin };
	Rectangle botBar = { 0.f, (float)screenHeight - margin , (float)screenWidth, margin };

	leftDark.x = std::lerp(-64.f, -halfWidth + margin, darkProgress);
	rightDark.x = std::lerp((float)screenWidth - margin, halfWidth +64.f, darkProgress);

	DrawRectangleRec(leftDark, BLACK);
	DrawRectangleRec(rightDark, BLACK);
	DrawRectangleRec(topBar, BLACK);
	DrawRectangleRec(botBar, BLACK);
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
		SetTile(x, y, L'.');
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
		tutorialPos1 = Vector2((float)x, (float)y);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'2')
	{
		tutorialPos2 = Vector2((float)x, (float)y);
		SetTile(x, y, L'.');
		return;
	}
	if (GetTile(x, y) == L'3')
	{
		tutorialPos3 = Vector2((float)x, (float)y);
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
	case L'L': // Climb Block
		src = { 80.f,0.f, 16.f, 16.f };
		break;
	case L'=': // Barrier Block
		src = { 80.f,16.f, 16.f, 16.f };
		break;
	case L'D': // Death Block
		src = { 80.f,32.f, 16.f, 16.f };
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
		src = { 80.f,48.f, 16.f, 16.f };
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
	// BossTime
	for (int i = 0; i < miscManager.GetBarrierList().size(); i++)
	{
		Vector2 pos = miscManager.GetBarrierList().at(i);
		SetTile(pos.x, pos.y, L'=');
	}
	enemyManager.SetBossActive(true);
	currentSong = currentBossSong;
	PlayMusicStream(currentSong);
}
