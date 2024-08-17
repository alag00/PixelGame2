#include "game.h"

Game::~Game()
{
	enemyManager.ClearEnemyList();
}
void Game::Run()
{
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Unholy Trek");
	InitAudioDevice();
	SetTargetFPS(60);

	background.SetSize(screenWidth, screenHeight);
	background.Setup();
	player.Setup();
	enemyManager.LoadEnemyTextures();
	enemyManager.GetPlayerRef(player);
	//enemy.Setup();
	//enemy.SetPlayerRef(player);

	LevelSetup();

	cam.offset = { screenWidth / 2.f, screenHeight / 2.f };
	cam.target = { screenWidth / 2.f, screenHeight / 2.f };
	cam.rotation = 0.f;
	cam.zoom = 1.f;

	filter.Setup(cam, screenWidth, screenHeight);

	
	tileTextures = LoadTexture("Assets/TileTextures/Textures.png");

	bossMusic = LoadMusicStream("Assets/Audio/Music/BossTheme.mp3");
	caveMusic = LoadMusicStream("Assets/Audio/Music/CaveTheme.mp3");

	currentSong = caveMusic;
	PlayMusicStream(currentSong);

	while (!WindowShouldClose())
	{
		Update();
		Render();
	}

	UnloadTexture(tileTextures);

	player.Unload();
	enemyManager.Unload();
	background.Unload();
	
	UnloadMusicStream(bossMusic);
	UnloadMusicStream(caveMusic);
	UnloadMusicStream(currentSong);

	CloseAudioDevice();
	CloseWindow();
}

void Game::Update()
{
	UpdateMusicStream(currentSong);
	float dt = GetFrameTime();
	filter.Update(dt);
	if (currentEvent != None)
	{
		CheckEvent();
		return;
	}
	
	CheckEvent();
	player.Update(dt);
	AdjustPlayer(dt);
	
	enemyManager.Update(dt);
	for (int i = 0; i < enemyManager.GetEnemyList().size(); i++)
	{
		if (!enemyManager.GetEnemyList().at(i)->IsAlive())
		{
			continue;
		}
		enemyManager.GetEnemyList().at(i)->Update(dt);
		if (player.IsInAttackMode())
		{
			player.CollisionCheck(*enemyManager.GetEnemyList().at(i));
		}
	}
	/*
	if ( boss != nullptr && !boss->IsAlive())
	{
		isBossActive = false;
	}
	*/
	float percent = (float)player.health / (float)player.maxHealth;
	if (percent <= 0.f)
	{
		filter.StartEffect(FADE_TO_BLACK);
		currentEvent = Die;
		player.health = 1;
		player.Die();
	}
}

void Game::CheckEvent()
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
		player.health = player.maxHealth;
		/*
		for (int i = 0; i < enemyList.size(); i++)
		{
			enemyList.at(i)->Reset();
			
		}
		*/
		enemyManager.Reset();
		enemyManager.SetBossActive(false);
		//isBossActive = false;
		break;
	}

	currentEvent = None;
}

void Game::AdjustPlayer(float dt)
{




	// Calculate potential new position
	float fNewPlayerPosX = player.GetPosition().x + player.GetVelocity().x * dt;
	float fNewPlayerPosY = player.GetPosition().y + player.GetVelocity().y * dt;

	/*
	if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 0.0f) == L'+')
	{
		//currentLevel++;
		//LevelSetup();
		filter.StartEffect(FADE_TO_BLACK);
		goNextLevel = true;
		return;
	}

	if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) == L'+')
	{
		//currentLevel++;
		//LevelSetup();
		filter.StartEffect(FADE_TO_BLACK);
		goNextLevel = true;
		return;
	}

	if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 0.0f) == L'+')
	{
		//currentLevel++;
		//LevelSetup();
		filter.StartEffect(FADE_TO_BLACK);
		goNextLevel = true;
		return;
	}

	if (GetTile(fNewPlayerPosX + 1.0f, fNewPlayerPosY + 1.0f) == L'+')
	{
		//currentLevel++;
		//LevelSetup();
		filter.StartEffect(FADE_TO_BLACK);
		goNextLevel = true;
		return;
	}
	*/

	// Check for Collision
	if (player.GetVelocity().x < 0) // Moving Left
	{

		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosX = (int)fNewPlayerPosX + 1;
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}
		/*
		if (tileTypeOne == L'D' || tileTypeTwo == L'D')
		{
			//
			LevelSetup();
			return;
		}
		if (tileTypeOne == L'+' || tileTypeTwo == L'+')
		{
			filter.StartEffect(FADE_TO_BLACK);
			goNextLevel = true;
			return;
		}
		*/
		/*
		if (GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.9f) != L'.')
		{
			if (GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.0f) == L'C' || GetTile(fNewPlayerPosX + 0.0f, player.GetPosition().y + 0.9f) == L'C')
			{
				player.SetOnGround(true);
			}
			fNewPlayerPosX = (int)fNewPlayerPosX + 1;
			player.SetVelocity(0.f, player.GetVelocity().y);
			
			//fPlayerVelX = 0;
		}
		*/
	}
	else if (player.GetVelocity().x > 0)// Moving Right
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.9f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosX = (int)fNewPlayerPosX;
				player.SetVelocity(0.f, player.GetVelocity().y);
			}
		}
		/*
		if (GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.0f) != L'.' || GetTile(fNewPlayerPosX + 1.0f, player.GetPosition().y + 0.9f) != L'.')
		{
			fNewPlayerPosX = (int)fNewPlayerPosX;
			player.SetVelocity(0.f, player.GetVelocity().y);
			//fPlayerVelX = 0;
		}
		*/
	}

	player.SetOnGround(false);
	//bPlayerOnGround = false;
	if (player.GetVelocity().y < 0) // Moving Up
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosY = (int)fNewPlayerPosY + 1;
				player.SetVelocity(player.GetVelocity().x, 0.f);
			}
		}
		/*
		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY) != L'.')
		{
			fNewPlayerPosY = (int)fNewPlayerPosY + 1;
			//	fPlayerVelY = 0;
			player.SetVelocity(player.GetVelocity().x, 0.f);
		}
		*/
	}
	else if (player.GetVelocity().y > 0) // Moving Down
	{
		char tileTypeOne = GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f);
		char tileTypeTwo = GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f);

		if (tileTypeOne != L'.' || tileTypeTwo != L'.')
		{
			if (IsPlayerTouchBlockTile(tileTypeOne, tileTypeTwo))
			{
				fNewPlayerPosY = (int)fNewPlayerPosY;
				player.SetVelocity(player.GetVelocity().x, 0.f);
				player.SetOnGround(true);
			}
		}
		/*
		if (GetTile(fNewPlayerPosX + 0.0f, fNewPlayerPosY + 1.0f) != L'.' || GetTile(fNewPlayerPosX + 0.9f, fNewPlayerPosY + 1.0f) != L'.')
		{
			fNewPlayerPosY = (int)fNewPlayerPosY;
			player.SetVelocity(player.GetVelocity().x, 0.f);
			//fPlayerVelY = 0;
			//bPlayerOnGround = true; // Player has a solid surface underfoot
			
			player.SetOnGround(true);
		}
		*/
	}

	// Apply new position
	player.SetPosition(fNewPlayerPosX, fNewPlayerPosY);
	//fPlayerPosX = fNewPlayerPosX;
	//fPlayerPosY = fNewPlayerPosY;
	background.Update(player.GetVelocity());
	// Link camera to player position
	fCameraPosX = player.GetPosition().x;
	fCameraPosY = player.GetPosition().y;
	
	

}

bool Game::IsPlayerTouchBlockTile(char tileTypeOne, char tileTypeTwo)
{
	if (tileTypeOne == L'#' || tileTypeTwo == L'#')
	{
		// Brick
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
	
	if (tileTypeOne == L'B' || tileTypeTwo == L'B')
	{
		// BossTime
		enemyManager.SetBossActive(true);
		currentSong = bossMusic;
		PlayMusicStream(currentSong);
		//isBossActive = true;
		return false;
	}

	if (tileTypeOne == L'C' || tileTypeTwo == L'C')
	{
		// CheckPoint
		// Set current checkpoint pos to this tile
		// when setting up new level, set spawn to current checkpoint
		

		currentCheckPoint = player.GetPosition();
		//SetTile(currentCheckPoint.x, currentCheckPoint.y, L'?');
		
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

		//goNextLevel = true;
		// NextLevel();
		return false;
	}
	if (tileTypeOne == L'-' || tileTypeTwo == L'-')
	{
		// Brick Background
		return false;
	}

	if (tileTypeOne == L',' || tileTypeTwo == L',')
	{
		// Stone Background
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
	return true;
}

void Game::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);
	RenderBackground();
	BeginMode2D(cam);

	LevelRender();

	RenderUI();
	filter.Render();
	EndMode2D();
	
	RenderHpBars();
	if (currentLevel == 1)
	{
		RenderTutorial();
	}
	//DrawText(TextFormat("Player Pos Y: %f", player.pos.y), 0, 20, 20, YELLOW);
	EndDrawing();
}

void Game::RenderUI()
{
	enemyManager.RenderUI();
	/*
	for (int i = 0; i < enemyList.size(); i++)
	{
		if (!enemyList.at(i)->IsAlive())
		{
			continue;
		}
		enemyList.at(i)->RenderUI();
	}
	*/
}
void Game::RenderBackground()
{
	background.Render();
}

void Game::LevelSetup()
{
	switch (currentLevel)
	{
	case 1:
		levels.CreateLevelOne();
		break;
	case 2:
		levels.CreateLevelTwo();
		break;
	case 3:
		levels.CreateLevelThree();
		break;
	case 4:
		levels.CreateLevelFour();
		break;
	case 5:
		levels.CreateLevelFive();
		break;
	default:
		levels.CreateLevelOne();
		break;
	}
	
	
	//boss = nullptr;

	sLevel = levels.GetLevel();
	nLevelWidth = levels.GetLevelWidth();
	nLevelHeight = levels.GetLevelHeight();

	//goNextLevel = false;

	background.SetLevelBackground(currentLevel);

	filter.StartEffect(FADE_FROM_BLACK);
	enemyManager.ClearEnemyList();

	int totalEnemies = 0;
	std::vector<Vector2> enemyPos{};

	for (int y = 0; y < nLevelHeight; y++)
	{
		for (int x = 0; x < nLevelWidth; x++)
		{
			
			if (GetTile(x, y) == L'S')
			{
				currentCheckPoint = { (float)x, (float)y };
				player.SetPosition(x , y );
				SetTile(x, y, L'.');
				continue;
			}
			if (GetTile(x, y) == L'K')
			{
				bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
				enemyManager.CreateKnight(Vector2(x, y), isBoss);
				SetTile(x, y, L'.');
				/*
				KnightEnemy* newEnemy = new KnightEnemy();
				newEnemy->SetPlayerRef(player);
				newEnemy->pos = Vector2(x,y);
				newEnemy->SetStartPos(Vector2(x, y));
				newEnemy->Setup();
				if (GetTile(x, y) == levels.GetBossChar())
				{
					boss = newEnemy;
					newEnemy->isBoss = true;
				}
				enemyList.push_back(newEnemy);
				SetTile(x, y, L'.');
				*/
				continue;
			}
			if (GetTile(x, y) == L'Z')
			{
				/*
				SkeletonEnemy* newEnemy = new SkeletonEnemy();
				newEnemy->SetPlayerRef(player);
				newEnemy->pos = Vector2(x, y);
				newEnemy->SetStartPos(Vector2(x, y));
				newEnemy->Setup();
				*/
				bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false ;
				enemyManager.CreateSkeleton(Vector2(x, y), isBoss);
				SetTile(x, y, L'.');
				/*
				if (GetTile(x, y) == levels.GetBossChar())
				{
					boss = newEnemy;
					newEnemy->isBoss = true;
				}
				enemyList.push_back(newEnemy);
				*/
				continue;
			}
			if (GetTile(x, y) == L'N')
			{
				bool isBoss = (GetTile(x, y) == levels.GetBossChar()) ? true : false;
				enemyManager.CreateNecromancer(Vector2(x, y), isBoss);
				SetTile(x, y, L'.');
				/*
				NecromancerEnemy* newEnemy = new NecromancerEnemy();
				newEnemy->SetPlayerRef(player);
				newEnemy->pos = Vector2(x, y);
				newEnemy->SetStartPos(Vector2(x, y));
				newEnemy->Setup();
				if (GetTile(x, y) == levels.GetBossChar())
				{
					boss = newEnemy;
					newEnemy->isBoss = true;
				}
				enemyList.push_back(newEnemy);
				SetTile(x, y, L'.');*/
				continue;
			}
			if(currentLevel != 1)
			{
				continue;
			}
			if (GetTile(x, y) == L'1')
			{
				tutorialPos1 = Vector2(x, y);
				SetTile(x, y, L'.');
				continue;
			}
			if (GetTile(x, y) == L'2')
			{
				tutorialPos2 = Vector2(x, y);
				SetTile(x, y, L'.');
				continue;
			}
			if (GetTile(x, y) == L'3')
			{
				tutorialPos3 = Vector2(x, y);
				SetTile(x, y, L'.');
				continue;
			}
		}
	}
	
}

void Game::LevelRender()
{
	// Draw Level
	int nTileWidth = 64;
	int nTileHeight = 64;
	int nVisibleTilesX = screenWidth / nTileWidth;
	int nVisibleTilesY = screenHeight / nTileHeight;



	cam.target = { fCameraPosX * nTileWidth, fCameraPosY * nTileHeight };
	// Clamp Camera
	float halfWidth = screenWidth / 2.f;
	float halfHeight = screenHeight / 2.f;
	
	if (cam.target.x < halfWidth) cam.target.x = halfWidth;
	if (cam.target.y < halfHeight) cam.target.y = halfHeight;
	if (cam.target.x > (nTileWidth * nLevelWidth) - halfWidth) cam.target.x = (nTileWidth * nLevelWidth) - halfWidth;
	if (cam.target.y > (nTileHeight * nLevelHeight) - halfHeight) cam.target.y = (nTileHeight * nLevelHeight) - halfHeight;

	fCameraPosX = cam.target.x / nTileWidth;
	fCameraPosY = cam.target.y / nTileHeight;


	Rectangle src{ 0.f,0.f, 16.f, 16.f };
	Rectangle dst{ 0.f, 0.f,0.f,0.f };
	Vector2 origin = { 0.f,0.f };
	// Draw visible tile map
	for (int y = (fCameraPosY - (nVisibleTilesY / 2.f) - 2) ; y < (fCameraPosY) +(nVisibleTilesY / 2.f) +1 ; y++)
	{
		for (int x = (fCameraPosX - (nVisibleTilesX / 2.f) - 2) ; x < (fCameraPosX ) +(nVisibleTilesX / 2.f) + 1  ; x++)
		{
			wchar_t sTileID = GetTile(x, y);
			switch (sTileID)
			{
			case L'.': // Sky
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, SKYBLUE);
				//DrawRectangle(x * nTileWidth, y * nTileHeight,  nTileWidth,  nTileHeight , SKYBLUE);
				break;
			case L'#':
				 src = {0.f,0.f, 16.f, 16.f};
				 dst = { (float)x * nTileWidth,(float) y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, RED);
				break;
			case L'_':
				src = {64.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, RED);
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, DARKBROWN);
				break;
			case L'%':
				src = { 32.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'-':
				src = { 0.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'*':
				src = { 16.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L',':
				src = { 16.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'C':
				src = { 96.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'?':
				src = { 96.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'{':
				src = { 80.f,0.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'}':
				src = { 80.f,16.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L'[':
				src = { 80.f, 32.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			case L']':
				src = { 80.f, 48.f, 16.f, 16.f };
				dst = { (float)x * nTileWidth,(float)y * nTileHeight,(float)nTileWidth, (float)nTileHeight };
				DrawTexturePro(tileTextures, src, dst, origin, 0.f, WHITE);
				break;
			
			default:
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, BLACK);
				DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, BLACK);
				break;
			}
		}
	}

	/*
	for (int i = 0; i < enemyList.size(); i++)
	{
		enemyList.at(i)->Render();
	}
	*/
	enemyManager.Render();
	player.Render();
	//Color color = GREEN;
	//color.a = 70;
	//DrawRectangle(player.GetPosition().x * nTileWidth , player.GetPosition().y * nTileHeight, nTileWidth, nTileHeight, color);

	/*
	// Draw Level
	int nTileWidth =  64;
	int nTileHeight = 64;
	int nVisibleTilesX = screenWidth / nTileWidth;
	int nVisibleTilesY = screenHeight / nTileHeight;

	// Calculate Top-Leftmost visible tile
	float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
	float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

	// Clamp camera to game boundaries
	if (fOffsetX < 0) fOffsetX = 0;
	if (fOffsetY < 0) fOffsetY = 0;
	if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
	if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

	// Get offsets for smooth movement
	float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
	float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

	// Draw visible tile map
	for (int x = -1; x < nVisibleTilesX + 1; x++)
	{
		for (int y = -1; y < nVisibleTilesY + 1; y++)
		{
			wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
			switch (sTileID)
			{
			case L'.': // Sky
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, SKYBLUE);
				DrawRectangle(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, SKYBLUE);
				break;
			case L'#': 
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, RED);
				DrawRectangle(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, nTileWidth, nTileHeight, RED);
				break;
			default:
				//DrawRectangle(x * nTileWidth, y * nTileHeight, nTileWidth, nTileHeight, BLACK);
				DrawRectangle(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, BLACK);
				break;
			}
		}
	}

	player.Render();
	DrawRectangle((player.GetPosition().x - fOffsetX) * nTileWidth, (player.GetPosition().y - fOffsetY) * nTileWidth, nTileWidth, nTileHeight, GREEN);
	*/
}

void Game::RenderTutorial()
{
	float tut1Dist = GetDist(player.pos, tutorialPos1);
	float tut2Dist = GetDist(player.pos, tutorialPos2);
	float tut3Dist = GetDist(player.pos, tutorialPos3);

	float range = 5.f;
	if (tut1Dist < range)
	{
		DrawText("'A and D' for Movement", screenWidth / 2.f, (screenHeight / 2.f) , 30, YELLOW);
		DrawText("'Space' to Jump", screenWidth / 2.f, (screenHeight / 2.f) + 30, 30, YELLOW);
	}
	else if (tut2Dist < range)
	{
		DrawText("'O' for Ordinary Attacks", screenWidth / 2.f, (screenHeight / 2.f) - 80, 30, YELLOW);
		DrawText("'P' to Parry", screenWidth / 2.f, (screenHeight / 2.f) - 50, 30, YELLOW);
	}
	else if (tut3Dist < range)
	{
		DrawText("Touch Glowing Gravestone to claim Checkpoint", 80, (screenHeight / 2.f) - 80, 30, YELLOW);
	}
}
char Game::GetTile(int x, int y)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
	{
		return sLevel[y * nLevelWidth + x];
	}
	return ' ';
}

void Game::SetTile(int x, int y, char c)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
	{
		sLevel[y * nLevelWidth + x] = c;
	}
}

/*
void Game::ClearEnemyList()
{

	for (int i = 0; i < enemyList.size(); i++)
	{
		delete enemyList.at(i);
		enemyList.at(i) = nullptr;
	}
	enemyList.clear();
}
*/

void Game::RenderHpBars()
{
	if (currentEvent == None)
	{
		Rectangle blackBar{ 20, screenHeight - 68.f , 200.f, 48.f };
		DrawRectangleRec(blackBar, BLACK);

		float margin = 5.f;
		Rectangle remainingHealth = { blackBar.x + margin, blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f };
		float percent = (float)player.health / (float)player.maxHealth;
		remainingHealth.width *= percent;

		DrawRectangleRec(remainingHealth, GREEN);

	}
	enemyManager.RenderBossBar();
	/*
	if (isBossActive)
	{
		Rectangle blackBar{ screenWidth / 2.f, screenHeight - 68.f , 500.f, 48.f };
		DrawRectangleRec(blackBar, BLACK);

		float margin = 5.f;
		Rectangle remainingHealth = { blackBar.x + margin, blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f };
		float percent = (float)boss->health / (float)boss->maxHealth;
		remainingHealth.width *= percent;

		DrawRectangleRec(remainingHealth, RED);
	}
	*/
}

float Game::GetDist(Vector2 vec1, Vector2 vec2)
{
	float x = vec1.x - vec2.x;
	float y = vec1.y - vec2.y;
	return sqrtf((x * x) + (y * y));
}