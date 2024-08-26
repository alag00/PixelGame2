#include "cutscene.h"

void CastleCutscene::Setup(Vector2&ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerIcon = LoadTexture("Assets/Icon.png");

	enemyIdle = LoadTexture("Assets/EnemyTextures/NecromancerEnemy/NecromancerEnemyIdleAtlas.png");
	enemyIcon = LoadTexture("Assets/Icon.png");

	enemyPos = {93.f, 8.f};
	enemySize.x = 144.f * scale;
	enemySize.y = 112.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 80.f, 8.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerWalk, 8, true);

	dialogue.QueueDialogue(false, enemyIcon, "GLORB GLORB GLORB");
	dialogue.QueueDialogue(false, enemyIcon, "GLORB A GLORB");
	dialogue.QueueDialogue(true, playerIcon, "OH GLORB");
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

	UnloadTexture(playerIcon);
	UnloadTexture(enemyIcon);
}

void GraveyardCutscene::Setup(Vector2& ref)
{
	camRef = &ref;

	playerIdle = LoadTexture("Assets/PlayerTextures/IdleAtlasAlter.png");
	playerWalk = LoadTexture("Assets/PlayerTextures/WalkAtlas.png");
	playerJump = LoadTexture("Assets/PlayerTextures/JumpAtlas.png");
	playerIcon = LoadTexture("Assets/Icon.png");

	enemyIdle = LoadTexture("Assets/EnemyTextures/Gnob/GnobIdleAtlas.png");
	enemyRest = LoadTexture("Assets/EnemyTextures/Gnob/GnobAttackOneAtlas.png");
	enemyIcon = LoadTexture("Assets/Icon.png");

	enemyPos = { 93.f, 8.f };
	enemySize.x = 80.f * scale;
	enemySize.y = 64.f * scale;
	enemyAnim.SetAnimation(enemyIdle, 8, true);

	playerPos = { 80.f, 8.f };
	playerSize.x = 48.f * scale;
	playerSize.y = 48.f * scale;
	playerAnim.SetAnimation(playerJump, 8, true);

	dialogue.QueueDialogue(true, playerIcon, "GLORB?");
	dialogue.QueueDialogue(false, enemyIcon, "GLORB?");
	dialogue.QueueDialogue(false, enemyIcon, "GLORB");
	dialogue.QueueDialogue(true, playerIcon, "GLORB");
}

bool GraveyardCutscene::Update(float dt)
{
	(void)dt;
	return false;
}

void GraveyardCutscene::Render()
{
}

void GraveyardCutscene::RenderUI()
{
	dialogue.Render();
}

void GraveyardCutscene::Unload()
{
	UnloadTexture(playerIdle);
	UnloadTexture(playerWalk);
	UnloadTexture(playerJump);

	UnloadTexture(enemyIdle);
	UnloadTexture(enemyRest);
	UnloadTexture(enemyIcon);
}
