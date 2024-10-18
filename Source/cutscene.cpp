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
			cutsceneStage = 5;
			playerAnim.CustomFPS(6.f);
			pauseTimer = PAUSE_TIME;
		}
		break;
	case 5:
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
	ref;
}

bool CastleBossCutscene::Update(float dt)
{
	dt;
	return true;
}

void CastleBossCutscene::Render()
{
}

void CastleBossCutscene::RenderUI()
{
}

void CastleBossCutscene::Unload()
{
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
	angelPort2 = LoadTexture("Assets/Portraits/PlayerPortrait.png");

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
	catPort = LoadTexture("Assets/Portraits/CatPortrait.png");

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

	dialogue.QueueDialogue(playerPort, catPort, "...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, catPort, "Your prayers has not been in vain.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, catPort, "I shall lend you some of my power.", false, PURPLE);
	dialogue.QueueDialogue(playerPort, catPort, "...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, catPort, "Now rise.", false, PURPLE);
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
	UnloadTexture(catPort);
}




void MansionBossCutscene::Setup(Vector2&ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");


	enemyIdle = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	enemyListenPort = LoadTexture("Assets/Portraits/NecromancerPortrait.png");
	enemySpeakPort = LoadTexture("Assets/Portraits/NecromancerPortraitTalk.png");

	enemyPos = {53.f, 54.f};
	enemySize.x = 144.f * scale;
	enemySize.y = 112.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 40.f, 54.f };
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
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "How long have you been standing there?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "...", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "What a minute, I remember you!", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "How are you still alive?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "Divine Intervention", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Is that so?", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "I'm back to take what's mine", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Fine, if you want to die so be it", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "Just another body for my collection", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "...", true, YELLOW);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "He He He", true, YELLOW);

	cutsceneStage = 2;
}

bool MansionBossCutscene::Update(float dt)
{
	UpdateSkipText(dt);
	playerAnim.UpdateAnimator(dt);
	enemyAnim.UpdateAnimator(dt);
	switch (cutsceneStage)
	{
	case 0:
		if (playerPos.x < 47.f)
		{
			playerPos.x += dt * 5.f;
			if (playerPos.x >= 47.f)
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
			if( enemyPos.x >= 53.f)
			{
				dialogue.SetActive(true);
				cutsceneStage = 3;
			}
		}
	
		break;
	case 3:
		if (!dialogue.GetActive())
		{
			return true;
		}
		break;
	}
	

	*camRef = { 50.f, 54.f };

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
	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f , enemySize.x, enemySize.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	
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


