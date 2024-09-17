#include "cutscene.h"

void CastleCutscene::Setup(Vector2&ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");
	//playerSpeakPort = LoadTexture("Assets/Icon.png");

	enemyIdle = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	enemyListenPort = LoadTexture("Assets/Portraits/NecromancerPortrait.png");
	enemySpeakPort = LoadTexture("Assets/Portraits/NecromancerPortraitTalk.png");

	enemyPos = {93.f, 8.f};
	enemySize.x = 144.f * scale;
	enemySize.y = 112.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 80.f, 8.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);

	dialogue.QueueDialogue(playerPort, enemySpeakPort, "GLORB GLORB GLORB", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemySpeakPort, "GLORB A GLORB", false, PURPLE);
	dialogue.QueueDialogue(playerPort, enemyListenPort, "OH GLORB", true, YELLOW);
}

bool CastleCutscene::Update(float dt)
{
	playerAnim.UpdateAnimator(dt);
	enemyAnim.UpdateAnimator(dt);
	switch (cutsceneStage)
	{
	case 0:
		if (playerPos.x < 87.f)
		{
			playerPos.x += dt * 5.f;
			if (playerPos.x >= 87.f)
			{
				playerAnim.SetAnimation(playerIdle, 8, true);
				enemyAnim.FlipAnimationHorizontal();
				enemyPos.x--;
				cutsceneStage = 1;
				dialogue.SetActive(true);
			}
		}
		break;
	case 1:
		if (!dialogue.GetActive())
		{
			cutsceneStage = 2;
		}
		break;
	case 2:
		return true;
	case 3:
		break;

	}
	

	*camRef = { 90.f, 8.f };

	dialogue.Update();

	if (IsKeyPressed(KEY_P))
	{
		return true;
	}

	return false;

}

void CastleCutscene::Render()
{
	// enemy
	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f , enemySize.x, enemySize.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	// player
	//dst = { pos.x * 64.f + 32.f, pos.y * 64.f + 40.f, size.x, size.y };
	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	
}

void CastleCutscene::RenderUI()
{
	dialogue.Render();
}

void CastleCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);
	UnloadTexture(enemyIdle);

	UnloadTexture(playerPort);
	//UnloadTexture(playerSpeakPort);
	UnloadTexture(enemyListenPort);
	UnloadTexture(enemySpeakPort);
}

void GraveyardCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	//playerJump = LoadTexture("Assets/PlayerTextures/JumpAtlas.png");

	playerPort = LoadTexture("Assets/Portraits/PlayerPortrait.png");
	//playerSpeakPort = LoadTexture("Assets/Icon.png");


	enemyIdle = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobIdleAtlas.png");
	enemyWalk = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobWalkAtlas.png");
	enemyRefill = LoadTexture("Assets/EnemyTextures/Gnob/FirstPhase/GnobRefillAtlas.png");
	enemyListenPort = LoadTexture("Assets/Portraits/GnobPortrait.png");
	enemySpeakPort = LoadTexture("Assets/Portraits/GnobPortraitTalk.png");

	enemyCol = { 90, 112, 100, 255 };
	enemyPos = { 238.f, 17.f };
	enemySize.x = 80.f * scale;
	enemySize.y = 64.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 225.f, 17.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);
	/*
	stage 1
			Player Walks to Pyro

	stage 2
		Player: Pyro?
			Pyro turns around

	stage 3
		Pyro: Oh, you have already made it this far
		Pyro: I heard what you did to Nekros
		Player:	...
		Player: I did I what I had to do
			Pyro turns and walks some steps away

	stage 4
		Pyro: Your vengance is understandable
		Pyro: Although, being able to take down Nekros
		Pyro: it's quite a remarkable feat I must say
		Pyro: Especially after what we took from you
		Player:	...
			Pyro turns around

	stage 5
		Pyro: ...
		Pyro: That glow?
		Player:	...
		Pyro: It's a shame...
		Pyro: I'm almost content with letting you go
		Pyro: But alas, Cryo would never let me allow Nekros murderer go
		Player: Enough speaking, lets fight
			Pyro walks slowly towards player
	
	stage 6
		Pyro: Agreed
		Pyro: Let us Draw our blades so that we may have our fun.
			Pyro Refills

	*/
	

	//dialogue.QueueDialogue(playerPort, enemyListenPort, "GLORB?", true, YELLOW);
	//dialogue.QueueDialogue(playerPort, enemySpeakPort, "GLORB?", false, GREEN);
	//dialogue.QueueDialogue(playerPort, enemySpeakPort, "GLORB", false, GREEN);
	//dialogue.QueueDialogue(playerPort, enemyListenPort, "GLORB", true, YELLOW);
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

	dialogue.SetActive(true);
	cutsceneStage = 8;
}

bool GraveyardCutscene::Update(float dt)
{
	playerAnim.UpdateAnimator(dt);
	enemyAnim.UpdateAnimator(dt);
	switch (cutsceneStage)
	{
	case 1: // GET TO POSITION
		playerPos.x += dt * 5.f;
		if (playerPos.x >= 232.f)
		{
			SetupStageTwo();
		}
		break;
	case 2: // SAY ONE LINE THEN ENEMY TURNS
		if (!dialogue.GetActive())
		{
			SetupStageThree();
		}
		break;
	case 3: // ENEMY TALKS THEN TURNS AND WALKS AWAY
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
		enemyPos.x -= dt * 2.f;
		if (enemyPos.x <= 238.f)
		{
			SetupStageEight();
		}
		break;
	case 8:
		if (!dialogue.GetActive())
		{
			return true;
		}
		break;
	

	}


	*camRef = { 237.f, 16.f };

	dialogue.Update();

	if (IsKeyPressed(KEY_P))
	{
		return true;
	}

	return false;

}

void GraveyardCutscene::Render()
{
	// enemy
	Rectangle dst = { enemyPos.x * 64.f , enemyPos.y * 64.f , enemySize.x, enemySize.y };
	Vector2 origin = { 0.f, dst.height * 0.5f + 32.f };// { dst.width * 0.35f, dst.height * 0.75f };
	enemyAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	// player
	//dst = { pos.x * 64.f + 32.f, pos.y * 64.f + 40.f, size.x, size.y };
	dst = { playerPos.x * 64.f, playerPos.y * 64.f + 40.f , playerSize.x, playerSize.y };
	origin = { dst.width / 2.f, dst.height / 2.f };
	playerAnim.DrawAnimationPro(dst, origin, 0.f, WHITE);


}

void GraveyardCutscene::RenderUI()
{
	dialogue.Render();
}

void GraveyardCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);

	UnloadTexture(enemyIdle);
	UnloadTexture(enemyWalk);
	UnloadTexture(enemyRefill);

	UnloadTexture(playerPort);
	//UnloadTexture(playerSpeakPort);
	UnloadTexture(enemyListenPort);
	UnloadTexture(enemySpeakPort);
}
