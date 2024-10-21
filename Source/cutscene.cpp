#include "cutscene.h"


void Cutscene::UpdateSkipText(float dt)
{
	blinkTimer -= dt;
	if (blinkTimer <= 0.f)
	{
		blinkTimer = BLINK_RATE;
		showSkipText = !showSkipText;
	}
}

void Cutscene::RenderSkipText()
{
	if (showSkipText)
	{
		txtRend.RenderText("Press 'P' to Skip", 30, 30, 30, WHITE, BLACK);
	}
}




IntroCutscene::IntroCutscene(Effect& filterRef)
{
	filter = &filterRef;
}

void IntroCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerFall = LoadTexture("Assets/PlayerTextures/BackFlipAtlas.png");
	playerRise = LoadTexture("Assets/PlayerTextures/StandUpAtlas.png");

	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerPos = { 5.f, 8.f };
	playerXOrigin = playerPos.x;
	playerAnim.SetAnimation(playerFall, 8, true);


	angelPos = { 7.f,30.f };
	angelYOrigin = angelPos.y;
	angelSize = {32.f * scale, 32.f * scale};
	angelCol.a = 0;

	angelTxr = LoadTexture("Assets/NPC/Disguise01.png");
	angelPort = LoadTexture("Assets/Portraits/AngelPortrait1.png");

	cutsceneStage = 1;
}

void IntroCutscene::SetupStageOne()
{
}

void IntroCutscene::SetupStageFour()
{
	
	dialogue.SetActive(true);
	cutsceneStage = 4;

	dialogue.QueueDialogue(Texture2D(), angelPort, "...", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "Damn! Those guys really f#%&ed you up.", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "Ehm, I said! Those guys really f#%&ed you up!", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, ".......", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "(There is no way she died right?)", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "a-are you dead?", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "...", false, YELLOW);

}

void IntroCutscene::SetupStageFive()
{
	dialogue.SetActive(true);
	cutsceneStage = 5;

	dialogue.QueueDialogue(Texture2D(), angelPort, "* SIGH *", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, " Good grief, very well.", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "I shall lend you some of my power.", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "...", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "Now help me fulfill my goal...", false, YELLOW);
	dialogue.QueueDialogue(Texture2D(), angelPort, "And wake up.", false, YELLOW);
}

bool IntroCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	switch (cutsceneStage)
	{
	case 1:
		speed += dt;
		playerPos.y += dt* speed;
		playerAnim.UpdateAnimator(dt);
		if (playerPos.y >= 30)
		{
			playerPos.y = 30.f;
			cutsceneStage = 2;
			playerAnim.SetAnimation(playerRise, 9, false);
			filter->StartEffect(FADE_TO_BLACK);
			//SetupStageThree();
		}
		*camRef = playerPos;
		break;
	case 2:
		//pauseTimer -= dt;

		if (!filter->IsActive())
		{
			
			if (!hasFadeOut )
			{
				hasFadeOut = true;
				filter->StartEffect(FADE_FROM_BLACK);
				
			}
			else 
			{
				cutsceneStage = 3;
			}
		}
		// FADe out and fade in
		break;
	case 3:
	{

		pauseTimer -= dt;
		float procent = pauseTimer / PAUSE_TIME;
		angelCol.a = (char)std::lerp(200, 0, procent);
		if (pauseTimer <= 0.f)
		{
			SetupStageFour();
		}
	}
		break;
	case 4:
		if (!dialogue.GetActive())
		{
			shakeProgress += dt * 16.f;
			playerPos.x = playerXOrigin + sin(shakeProgress) / 20.f;
			if (shakeProgress >= 8.f)
			{
				SetupStageFive();
			}
		}
		break;
	case 5: // after player shakes
		if (!dialogue.GetActive())
		{
			cutsceneStage = 6;
			playerAnim.CustomFPS(6.f);
			pauseTimer = PAUSE_TIME;
		}
		break;
	case 6:
	{

		pauseTimer -= dt;
		
		if (pauseTimer <= 0.f)
		{
			angelCol.a = 0;
			playerAnim.UpdateAnimator(dt);
			if (playerAnim.GetCurrentFrame() >= 8)
			{
				return true;
			}
		}
		else
		{
			float procent = pauseTimer / PAUSE_TIME;
			angelCol.a = (char)std::lerp(0, 200, procent);
		}
	}
		break;
	}
	dialogue.Update(dt);
	progress += dt;
	angelPos.y = angelYOrigin + sin(progress) / 2.f;

	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}

	
	return false;
}

void IntroCutscene::Render()
{
	Rectangle dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	if (!hasFadeOut)
	{
		return;
	}
	Rectangle src = { 0.f,0.f, (float)angelTxr.width, (float)angelTxr.height };
	dst = { angelPos.x * 64.f, angelPos.y * 64.f , angelSize.x, angelSize.y };
	DrawTexturePro(angelTxr, src, dst, origin, 0.f, angelCol);
}

void IntroCutscene::RenderUI()
{
	dialogue.Render();
	RenderSkipText();
}

void IntroCutscene::Unload()
{
	UnloadTexture(playerFall);
	UnloadTexture(playerRise);
	UnloadTexture(angelTxr);
	UnloadTexture(angelPort);
}




void CastleBossCutscene::Setup(Vector2& ref)
{
	camRef = &ref;


	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerHurt = LoadTexture("Assets/PlayerTextures/DamagedAtlas.png");
	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");

	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerPos = { 80.f, 8.f };
	playerAnim.SetAnimation(playerWalk, 8, true);


	enemyFall = LoadTexture("Assets/EnemyTextures/Executioner/ExecutionerFallAtlas.png");
	enemyDash = LoadTexture("Assets/EnemyTextures/Executioner/ExecutionerInitGrabAtlas.png");
	enemyGrab = LoadTexture("Assets/EnemyTextures/Executioner/ExecutionerGrabHitAtlas.png");
	enemyIdle = LoadTexture("Assets/EnemyTextures/Executioner/ExecutionerIdleAtlas.png");

	enemyPort = LoadTexture("Assets/Portraits/ExecutionerPortrait.png");
	enemySize.x = 112.f * scale;
	enemySize.y = 112.f * scale;
	enemyPos = { 85.f, -5.f };
	enemyStartX = enemyPos.x;
	enemyAnim.SetAnimation(enemyFall, 2, true);
	enemyAnim.FlipAnimationHorizontal();

	angelPos = { 90.f,8.f };
	angelYOrigin = angelPos.y;
	angelSize = { 32.f * scale, 32.f * scale };
	angelCol.a = 0;

	angelTxr = LoadTexture("Assets/NPC/Disguise01.png");
	angelPort = LoadTexture("Assets/Portraits/AngelPortrait1.png");

	cutsceneStage = 1;
}

void CastleBossCutscene::SetupStageSix()
{
	dialogue.SetActive(true);
	cutsceneStage = 6;

	dialogue.QueueDialogue(playerPort, enemyPort, "What the hell.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemyPort, "Hey You! Let me through.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemyPort, "YOU FOOL!", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyPort, "YOU ARE NO LONGER WELCOME HERE!", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyPort, "BUT BECAUSE OF YOUR SERVICE...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyPort, "I SHALL GIVE YOU ONE LAST WARNING!", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyPort, "What?", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemyPort, "LEAVE.", false, PURPLE);

	playerAnim.SetAnimation(playerIdle, 8, true);
	enemyAnim.FlipAnimationHorizontal();
}

void CastleBossCutscene::SetupStageEigth()
{
	dialogue.SetActive(true);
	cutsceneStage = 8;

	dialogue.QueueDialogue(angelPort, enemyPort, "That's not happening pal.", true, YELLOW);
	dialogue.QueueDialogue(angelPort, enemyPort, "Y-YOU! Why are you here?!", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemyPort, "To restore the balance of course.", true, YELLOW);
	dialogue.QueueDialogue(angelPort, enemyPort, "But you won't be alive to see it.", true, YELLOW);
	dialogue.QueueDialogue(angelPort, enemyPort, "...", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemyPort, "Change of plans, you aint going anywhere.", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemyPort, "I must stop you before it's too late.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, angelPort, "Look out for his grab techniques.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort, "Aw man.", true, YELLOW);
}

void CastleBossCutscene::PlayerGrabPosition()
{
	
	if (enemyAnim.GetCurrentFrame() == 0)
	{
		playerPos.y = enemyPos.y;
		playerPos.x = enemyPos.x + 1.5f;
	}
	else if (enemyAnim.GetCurrentFrame() == 1)
	{
		playerPos.y = enemyPos.y;
		playerPos.x = enemyPos.x + 0.5f;
	}
	else if (enemyAnim.GetCurrentFrame() >= 2 && enemyAnim.GetCurrentFrame() <= 8)
	{
		playerPos.y = enemyPos.y - 0.5f;
		playerPos.x = enemyPos.x - 0.2f;
	}
	else if (enemyAnim.GetCurrentFrame() >= 9)
	{
		cutsceneStage = 5;
		playerAnim.SetAnimation(playerHurt, 8, false);
		enemyAnim.SetAnimation(enemyIdle, 4, true);
		enemyAnim.CustomFPS(6.f);
		playerVelY = -5.f;
	}
}

bool CastleBossCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}
	playerAnim.UpdateAnimator(dt);
	
	switch (cutsceneStage)
	{
	case 1:
		// player walks
		playerPos.x += dt * PLAYER_SPEED;
		if (playerPos.x > 92.f)
		{
			cutsceneStage = 2;
		}
		break;
	case 2:
		// guardian drops down from sky
		enemyPos.y += dt * ENEMY_FALL_SPEED;
		playerPos.x += dt * PLAYER_SPEED;
		if (enemyPos.y >= 7.f)
		{
			enemyPos.y = 7.f;
			cutsceneStage = 3;
			enemyAnim.SetAnimation(enemyDash, 10, false);
		}
		break;
	case 3:
		// guardian dashes towards player with grab dash animation
		playerPos.x += dt * PLAYER_SPEED;
		if (pauseTimer > 0.f && enemyAnim.GetCurrentFrame() == 1)
		{
			pauseTimer -= dt;
			return false;
		}
		enemyDashProgress += dt * 1.5f;
		enemyPos.x = std::lerp(enemyStartX, playerPos.x - 2.f, enemyDashProgress);
		if (enemyDashProgress >= 1.f)
		{
			cutsceneStage = 4;
			enemyAnim.SetAnimation(enemyGrab, 10, false);
			playerAnim.SetAnimation(playerIdle, 8, true);
			enemyAnim.CustomFPS(6.f);
		}
		break;
	case 4:
		// guardian does grab hit animation
		PlayerGrabPosition();
		break;
	case 5:
		// player flies back
		playerPos.x -= dt * PLAYER_SPEED;
		playerPos.y += playerVelY * dt;
		playerVelY += dt * 5.f;
		if (playerPos.y >= 8.f)
		{
			SetupStageSix();
		}
		break;
	case 6:
		// dialogue starts
		if (!dialogue.GetActive())
		{
			cutsceneStage = 7;
			pauseTimer = PAUSE_TIME;
		}
		break;
	case 7:
	{
		// angel appears
		pauseTimer -= dt;
		float procent = pauseTimer / PAUSE_TIME;
		angelCol.a = (char)std::lerp(200, 0, procent);
		if (pauseTimer <= 0.f)
		{
			SetupStageEigth();
		}
	}
		break;
	case 8:
		// more dialogue
		if (!dialogue.GetActive())
		{
			return true;
		}
		break;
	}

	enemyAnim.UpdateAnimator(dt);
	
	*camRef = { 96.f, 6.f };
	dialogue.Update(dt);
	progress += dt;
	angelPos.y = angelYOrigin + sin(progress) / 2.f;

	
	

	return false;
}

void CastleBossCutscene::Render()
{
	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f + 128.f , enemySize.x, enemySize.y };
	Vector2 origin = { dst.width * 0.35f , dst.height  };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	Rectangle src = { 0.f,0.f, (float)angelTxr.width, (float)angelTxr.height };
	src.width = -src.width;
	dst = { angelPos.x * 64.f, angelPos.y * 64.f , angelSize.x, angelSize.y };
	DrawTexturePro(angelTxr, src, dst, origin, 0.f, angelCol);
}

void CastleBossCutscene::RenderUI()
{
	dialogue.Render();
	RenderSkipText();
}

void CastleBossCutscene::Unload()
{
	UnloadTexture(playerWalk);
	UnloadTexture(playerHurt);
	UnloadTexture(playerIdle);

	UnloadTexture(enemyFall);
	UnloadTexture(enemyDash);
	UnloadTexture(enemyGrab);
	UnloadTexture(enemyIdle);

	UnloadTexture(angelTxr);

	UnloadTexture(playerPort);
	UnloadTexture(enemyPort);
	UnloadTexture(angelPort);
}




void CastleCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");

	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerPos = { 1.f, 10.f };
	playerAnim.SetAnimation(playerWalk, 8, true);


	angelPos = { 28.f,10.f };
	angelYOrigin = angelPos.y;
	angelSize = { 32.f * scale, 32.f * scale };
	angelCol.a = 0;

	angelTxr1 = LoadTexture("Assets/NPC/Disguise01.png");
	angelTxr2 = LoadTexture("Assets/NPC/Disguise02.png");
	angelPort1 = LoadTexture("Assets/Portraits/AngelPortrait1.png");
	angelPort2 = LoadTexture("Assets/Portraits/AngelPortrait2.png");

	cutsceneStage = 1;
}

void CastleCutscene::SetupStageThree()
{
	dialogue.SetActive(true);
	cutsceneStage = 3;

	dialogue.QueueDialogue(playerPort, angelPort1, "...", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "Good job defeating that nasty guardian", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "Yeah but what he mean by...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "That guy was a gate keeper and an executioner!", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "Don't trust a word he said.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "I guess you are right but...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "Anyway! don't worry about...", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "But...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "No buts...", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "What's going on here?!", true, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "You want the truth?", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort1, "Fine. Here it is.", false, YELLOW);

	pauseTimer = PAUSE_TIME;
}

void CastleCutscene::SetupStageFour()
{
	hasRevealed = true;
	dialogue.SetActive(true);
	cutsceneStage = 4;

	dialogue.QueueDialogue(playerPort, angelPort2, "I am an servant of the Great One...", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "In other words, one of your God's Angels.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "I was sent here to assist you in fullfilling your goal.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "Which is killing the 3 Mancers to restore the balance.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "Necromancer...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, angelPort2, "Pyromancer...", false, ORANGE);
	dialogue.QueueDialogue(playerPort, angelPort2, "Cryomancer...", false, SKYBLUE);
	dialogue.QueueDialogue(playerPort, angelPort2, "You need my help for your revenge...", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "Otherwise you wouldn't be at the bottom of that cave.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort2, "A#%&$#@", true, YELLOW);

}

bool CastleCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	playerAnim.UpdateAnimator(dt);
	dialogue.Update(dt);
	progress += dt;
	angelPos.y = angelYOrigin + sin(progress) / 2.f;
	*camRef = playerPos;

	switch (cutsceneStage)
	{
	case 1:
		playerPos.x += dt * speed;
		if (playerPos.x >= 24.f)
		{
			playerPos.x = 24.f;
			cutsceneStage = 2;
			playerAnim.SetAnimation(playerIdle, 8, true);
		}
		break;
	case 2:
	{
		pauseTimer -= dt;
		if (!hasPausedOnce && pauseTimer <= 0.f)
		{
			hasPausedOnce = true;
			pauseTimer = PAUSE_TIME;
		}
		if (hasPausedOnce)
		{
			float procent = pauseTimer / PAUSE_TIME;
			angelCol.a = (char)std::lerp(200, 0, procent);
			if (pauseTimer <= 0.f)
			{
				SetupStageThree();
			}
		}
	}
		break;
	case 3:
		if (!dialogue.GetActive())
		{
			SetupStageFour();
		}
		break;
	case 4:
		if (!dialogue.GetActive())
		{
			cutsceneStage = 5;
		}
		break;
	case 5:
	{
		pauseTimer -= dt;
		float procent = pauseTimer / PAUSE_TIME;
		angelCol.a = (char)std::lerp(0, 200, procent);
		if (pauseTimer <= 0.f)
		{
			return true;
		}
	}
	break;
	}
	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}
	return false;
}

void CastleCutscene::Render()
{
	Rectangle dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	Vector2 origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);


	Rectangle src = { 0.f,0.f, (float)angelTxr1.width, (float)angelTxr1.height };
	dst = { angelPos.x * 64.f, angelPos.y * 64.f , angelSize.x, angelSize.y };
	if (!hasRevealed)
	{
		
		DrawTexturePro(angelTxr1, src, dst, origin, 0.f, angelCol);
		return;
	}
	DrawTexturePro(angelTxr2, src, dst, origin, 0.f, angelCol);
}

void CastleCutscene::RenderUI()
{
	dialogue.Render();
	RenderSkipText();
}

void CastleCutscene::Unload()
{
	UnloadTexture(angelTxr1);
	UnloadTexture(angelTxr2);
	UnloadTexture(angelPort1);
	UnloadTexture(angelPort2);

	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);
	UnloadTexture(playerPort);
}




void CatCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");

	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");


	catIdle = LoadTexture("Assets/NPC/CatsIdleAtlas.png");
	catLeave = LoadTexture("Assets/NPC/CatsLeaveAtlas.png");
	cat1Port = LoadTexture("Assets/Portraits/CatPortrait.png");
	cat2Port = LoadTexture("Assets/Portraits/Cat2Portrait.png");

	catPos = { 5.f, 17.f };
	catSize.x = 32.f * scale;
	catSize.y = 32.f * scale;
	catAnim.SetAnimation(catIdle, 8, true);

	playerPos = { 1.f, 17.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);

	cutsceneStage = 1;
}

void CatCutscene::SetupStageTwo()
{

	playerAnim.SetAnimation(playerIdle, 8, true);
	cutsceneStage = 2;
	dialogue.SetActive(true);

	dialogue.QueueDialogue(playerPort, cat1Port, "Oh, a visitor?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "A cat with a hat, Cool.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, cat1Port, "Oh, and a live one at that.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "Isn't that right Mr. Whiskyscratch?.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat2Port, "Meow.", false, DARKGRAY);
	dialogue.QueueDialogue(playerPort, cat1Port, "So true.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "Anyway. Welcome to my domain mortal.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "I would have Mr. Whiskyscratch offer you some tea...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "But frankly I am unable to...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "As a necromancer has taken my manor.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "A Necromancer you say?", true, YELLOW);
	dialogue.QueueDialogue(playerPort, cat1Port, "I happened to specialize in terminating such problems.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, cat1Port, "Is that so?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "That would be wonderful.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, cat1Port, "Just follow the road and you will be right there.", false, PURPLE);
}

bool CatCutscene::Update(float dt)
{
	playerAnim.UpdateAnimator(dt);
	catAnim.UpdateAnimator(dt);
	UpdateSkipText(dt);
	dialogue.Update(dt);
	*camRef = playerPos;
	switch (cutsceneStage)
	{
	case 1:
		playerPos.x += dt * PLAYER_SPEED;
		if (playerPos.x >= 4.f)
		{
			SetupStageTwo();
		}
		break;
	case 2:
		if (!dialogue.GetActive())
		{
			pauseTimer -= dt;
			if (pauseTimer <= 0.f)
			{
				cutsceneStage = 3;
				catAnim.SetAnimation(catLeave, 10, false);
				catAnim.CustomFPS(9.f);
				pauseTimer = PAUSE_TIME;
			}
		}
		break;
	case 3:
		// Cat disappears
		if (catAnim.GetCurrentFrame() >= 9)
		{
			pauseTimer -= dt;
			if (pauseTimer <= 0.f)
			{
				return true;
			}
		}
		break;
	}
	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}
	return false;
}

void CatCutscene::Render()
{

	Rectangle dst = { catPos.x * 64.f , catPos.y * 64.f , catSize.x, catSize.y };
	Vector2 origin = { 0.f, 32.f};
	catAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);


	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

}

void CatCutscene::RenderUI()
{
	dialogue.Render();
	RenderSkipText();
}

void CatCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);
	UnloadTexture(playerPort);

	UnloadTexture(catIdle);
	UnloadTexture(catLeave);
	UnloadTexture(cat1Port);
	UnloadTexture(cat2Port);
}




void MansionBossCutscene::Setup(Vector2&ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");


	enemyIdle = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	enemyTeleport = LoadTexture("Assets/NPC/NecromancerTeleportAtlas.png");
	enemyListenPort = LoadTexture("Assets/Portraits/NecromancerPortrait.png");
	enemySpeakPort = LoadTexture("Assets/Portraits/NecromancerPortraitTalk.png");

	angelTxr = LoadTexture("Assets/NPC/Disguise02.png");
	angelPort = LoadTexture("Assets/Portraits/AngelPortrait2.png");

	angelPos = { 57.f, 58.f };
	angelYOrigin = angelPos.y;
	angelSize = { 32.f * scale, 32.f * scale };
	angelCol.a = 0;

	enemyPos = {60.f, 57.5f};
	enemySize.x = 144.f * scale;
	enemySize.y = 112.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 45.f, 59.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);

	
	
	
}

void MansionBossCutscene::SetupStageOne()
{
	playerAnim.SetAnimation(playerIdle, 8, true);

	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Hm, now where did I put my necromancy books?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "I could have sworn I put it right here...", false, PURPLE);

	dialogue.SetActive(true);
	cutsceneStage = 1;
}

void MansionBossCutscene::SetupStageTwo()
{
	



	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Woah!", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Oh it's just you..", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Jesus, How long have you been standing there?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Anyway how do you like the new crib, I stole from some...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "What a minute, You are supposed to be dead.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "How are you still alive?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "Divine Intervention", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Is that so?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Well you look a little different...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "You have a glowing aura around you.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "Thanks, I have been following some guides.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "No I mean like you have a literal glowing aura around you.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "Oh that, that's from my angel.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Angel?", false, PURPLE);

	cutsceneStage = 2;
}

void MansionBossCutscene::SetupStageFive()
{
	dialogue.QueueDialogue(angelPort, enemyListenPort, "Hello Victor, long time no see.", true, YELLOW);
	dialogue.QueueDialogue(angelPort, enemyListenPort, "Y-you...", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemyListenPort, "Why are you here?", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemyListenPort, "Oh? isn't it obvious?", true, YELLOW);
	dialogue.QueueDialogue(angelPort, enemySpeakPort, "Than that means that...", false, PURPLE);
	dialogue.QueueDialogue(angelPort, enemySpeakPort, "Nah man F#%$ this!", false, PURPLE);
	cutsceneStage = 5;
	dialogue.SetActive(true);
}

void MansionBossCutscene::SetupStageSeven()
{
	dialogue.QueueDialogue(playerPort, angelPort, "I guess he wasn't as excited for the reunion as I was.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort, "He can't have gotten far.", true, YELLOW);
	dialogue.QueueDialogue(playerPort, angelPort, "True that, it is likely that he is still in this building.", false, YELLOW);
	dialogue.QueueDialogue(playerPort, Texture2D(), "N-no I'm not", false, PURPLE);
	dialogue.QueueDialogue(playerPort, Texture2D(), "Just don't check upstairs.", false, PURPLE);
	cutsceneStage = 7;
	dialogue.SetActive(true);
}

bool MansionBossCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	playerAnim.UpdateAnimator(dt);
	enemyAnim.UpdateAnimator(dt);
	switch (cutsceneStage)
	{
	case 0:
		if (playerPos.x < 50.f)
		{
			playerPos.x += dt * 5.f;
			if (playerPos.x >= 50.f)
			{
				SetupStageOne();
			}
		}
		break;
	case 1:
		if (!dialogue.GetActive())
		{
			SetupStageTwo();
		}
		break;
	case 2:
		pauseTimer -= dt;
		if (pauseTimer <= 0.f)
		{
			if (!enemyFlipped)
			{
				//pauseTimer = PAUSE_TIMER;
				enemyAnim.FlipAnimationHorizontal();
				enemyPos.x--;
				enemyFlipped = true;
			}

			enemyPos.x += ENEMY_SCARED_SPEED * dt;
			if( enemyPos.x >= 62.f)
			{
				dialogue.SetActive(true);
				cutsceneStage = 3;
			}
		}
	
		break;
	case 3:
		if (!dialogue.GetActive())
		{
			cutsceneStage = 4;
		}
		break;
	case 4:
		// angel spawns in
		pauseTimer -= dt;
		if (!hasPausedOnce && pauseTimer <= 0.f)
		{
			hasPausedOnce = true;
			pauseTimer = PAUSE_TIME;
		}
		if (hasPausedOnce)
		{
			float procent = pauseTimer / PAUSE_TIME;
			angelCol.a = (char)std::lerp(200, 0, procent);
			if (pauseTimer <= 0.f)
			{
				SetupStageFive();
			}
		}
		break;
	case 5:
		// more dialogue
		if (!dialogue.GetActive())
		{
			cutsceneStage = 6;
			enemyAnim.SetAnimation(enemyTeleport, 16, false);
		}
		break;
	case 6:
		// enemy teleport away
		if (enemyAnim.GetCurrentFrame() >= 15)
		{
			SetupStageSeven();
		}
		break;
	case 7:
		// final dialogue
		if (!dialogue.GetActive())
		{
			return true;
		}
		break;
	}
	

	*camRef = { 60.f, 56.f };
	progress += dt;
	angelPos.y = angelYOrigin + sin(progress) / 2.f;
	dialogue.Update(dt);

	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}

	return false;

}

void MansionBossCutscene::Render()
{
	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f + 8.f , enemySize.x, enemySize.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	Rectangle src = { 0.f,0.f, (float)angelTxr.width, (float)angelTxr.height };
	src.width = -src.width;
	dst = { angelPos.x * 64.f, angelPos.y * 64.f , angelSize.x, angelSize.y };
	DrawTexturePro(angelTxr, src, dst, origin, 0.f, angelCol);
}

void MansionBossCutscene::RenderUI()
{
	dialogue.Render();
	RenderSkipText();

}

void MansionBossCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);
	UnloadTexture(enemyIdle);

	UnloadTexture(playerPort);

	UnloadTexture(enemyListenPort);
	UnloadTexture(enemySpeakPort);

	UnloadTexture(angelPort);
	UnloadTexture(angelTxr);
}




void GraveyardCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");

	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");
	

	enemyIdle = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobIdleAtlas.png");
	enemyWalk = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobWalkAtlas.png");
	enemyRefill = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobRefillAtlas.png");
	enemyListenPort = LoadTexture("Assets/Portraits/GnobPortrait.png");
	enemySpeakPort = LoadTexture("Assets/Portraits/GnobPortraitTalk.png");


	enemyPos = { 238.f, 17.f };
	enemySize.x = 80.f * scale;
	enemySize.y = 64.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 225.f, 17.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);
	
}

void GraveyardCutscene::SetupStageOne()
{

}

void GraveyardCutscene::SetupStageTwo()
{
	playerAnim.SetAnimation(playerIdle, 8, true);

	dialogue.QueueDialogue(playerPort, enemyListenPort, "Pyro?", true, YELLOW);

	dialogue.SetActive(true);
	cutsceneStage = 2;
}

void GraveyardCutscene::SetupStageThree()
{
	enemyAnim.FlipAnimationHorizontal();
	enemyPos.x--;

	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Oh, you have already made it this far", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "I heard what you did to Nekros", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "I did I what I had to do", true, YELLOW);

	dialogue.SetActive(true);
	cutsceneStage = 3;
}

void GraveyardCutscene::SetupStageFour()
{
	enemyAnim.SetAnimation(enemyWalk, 8, true);
	enemyAnim.FlipAnimationHorizontal();
	enemyPos.x++;

	cutsceneStage = 4;
}

void GraveyardCutscene::SetupStageFive()
{
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	dialogue.QueueDialogue(playerPort, enemySpeakPort, "As will I", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Your vengance is understandable", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, " Although, being able to take down Nekros", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "For someone like you", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "it's quite a remarkable feat I must say", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Especially after what we took from you", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);

	dialogue.SetActive(true);
	cutsceneStage = 5;
}

void GraveyardCutscene::SetupStageSix()
{
	enemyAnim.FlipAnimationHorizontal();
	enemyPos.x--;

	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "That glow", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "I see, It's a shame", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "I'm almost content with letting you go", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "But alas, Cryo would never let me allow Nekros murderer go", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "Enough speaking, lets fight", true, YELLOW);

	dialogue.SetActive(true);
	cutsceneStage = 6;
}

void GraveyardCutscene::SetupStageSeven()
{
	enemyAnim.SetAnimation(enemyWalk, 8, true);
	cutsceneStage = 7;
}

void GraveyardCutscene::SetupStageEight()
{
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Agreed", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Let us Draw our blades so that we may have our fun.", false, enemyCol);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "He He He", true, YELLOW);

	dialogue.SetActive(true);
	cutsceneStage = 8;
}

void GraveyardCutscene::SetupStageNine()
{
	enemyAnim.SetAnimation(enemyRefill, 12, false);
	cutsceneStage = 9;
}

bool GraveyardCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	playerAnim.UpdateAnimator(dt);
	enemyAnim.UpdateAnimator(dt);
	switch (cutsceneStage)
	{
	case 1: 
		playerPos.x += dt * 5.f;
		if (playerPos.x >= 232.f)
		{
			SetupStageTwo();
		}
		break;
	case 2: 
		if (!dialogue.GetActive())
		{
			SetupStageThree();
		}
		break;
	case 3: 
		if (!dialogue.GetActive())
		{
			SetupStageFour();
		}
		break;
	case 4:
		enemyPos.x += dt * 3.f;
		if (enemyPos.x >= 240.f)
		{
			SetupStageFive();
		}
		break;
	case 5:
		if (!dialogue.GetActive())
		{
			SetupStageSix();
		}
		break;
	case 6:
		if (!dialogue.GetActive())
		{
		
			SetupStageSeven();
			
		}
		break;
	case 7:
		enemyPos.x -= dt * 3.f;
		if (enemyPos.x <= 237.f)
		{
			SetupStageEight();
		}
		break;
	case 8:
		if (!dialogue.GetActive())
		{
			SetupStageNine();
		}
		break;
	case 9:
		if (enemyAnim.GetCurrentFrame() >= 11)
		{
			return true;
		}
		break;
	

	}


	*camRef = { 237.f, 16.f };

	dialogue.Update(dt);

	if (IsKeyPressed(KEY_P))
	{
		dialogue.SetActive(false);
		return true;
	}

	return false;

}

void GraveyardCutscene::Render()
{

	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f , enemySize.x, enemySize.y };
	Vector2 origin = { 0.f, dst.height * 0.5f + 32.f };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);


	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);


}

void GraveyardCutscene::RenderUI()
{
	dialogue.Render();

	RenderSkipText();

}

void GraveyardCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);

	UnloadTexture(enemyIdle);
	UnloadTexture(enemyWalk);
	UnloadTexture(enemyRefill);

	UnloadTexture(playerPort);

	UnloadTexture(enemyListenPort);
	UnloadTexture(enemySpeakPort);
}


