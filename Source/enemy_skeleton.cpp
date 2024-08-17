#include "enemy_skeleton.h"

SkeletonEnemy::~SkeletonEnemy() 
{ 
	playerRef = nullptr;

	UnloadTexture(idleAtlas);
	UnloadTexture(deathAtlas);
	UnloadTexture(attackAtlas);
	UnloadTexture(blockAtlas);
}

void SkeletonEnemy::SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D attackTxr, Texture2D blockTxr)
{
	idleAtlas = idleTxr;
	deathAtlas = deathTxr;
	attackAtlas = attackTxr;
	blockAtlas = blockTxr;
}

void SkeletonEnemy::Setup()
{

	//blockAtlas = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeflectAtlas.png");
	//deathAtlas = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyDeathAtlas.png");
	//idleAtlas = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyIdleAtlas.png");
	//attackAtlas = LoadTexture("Assets/EnemyTextures/SkeletonEnemy/SkeletonEnemyAttackAtlas.png");

	size.x = 64.f * scale;
	size.y = 64.f * scale;

	anim.SetAnimation(idleAtlas, 8, true);

	maxHealth = 30;
	health = maxHealth;
}

void SkeletonEnemy::Sense()
{
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf((x * x) + (y * y));

	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED)
	{
		return;
	}
	if (lookRight && pos.x < playerRef->pos.x || !lookRight && pos.x > playerRef->pos.x)
	{
		lookRight = !lookRight;
		anim.FlipAnimationHorizontal();
	}
}
void SkeletonEnemy::Decide() {
	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED)
	{
		return;
	}
	if (distance <= 2.f && attackTimer <= 0.f)
	{
		dec = DECISION::ATTACK;
		anim.SetAnimation(attackAtlas, 14, false);
		currentAttackId++;
		//size.x = 80.f * scale;
		//size.y = 80.f * scale;
	}
	else
	{
		dec = DECISION::IDLE;
		//anim.SetAnimation(idleAtlas, 8, false);
	}
}
void SkeletonEnemy::Act(float dt) {
	attackTimer -= dt;
	hitBox = { pos.x, pos.y - 1.f , 1.5f,2.f };
	hitBox.x = (lookRight) ? pos.x - 1.f : pos.x - 0.5f;
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::ATTACK:
		Attack(dt);
		break;
	case DECISION::DAMAGED:
		if (anim.GetCurrentFrame() >= 4)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(idleAtlas, 8, true);
			attackTimer = attackCooldown;
			if (health <= 0)
			{
				SetIsAlive(false);
				anim.SetAnimation(deathAtlas, 8, false);
			}
		}
		break;
	}
}

void SkeletonEnemy::Render() {

	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 64.f , size.x, size.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f};//{ pos.x + (dst.width / 2.f), pos.y + (dst.height / 2.f) };
	dst.x = (lookRight) ? dst.x - 64.f : dst.x;
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	//Color color = YELLOW;
	//color.a = 50;
	//DrawCircle(pos.x * 64.f, pos.y * 64.f, 100.f, color);
	// DrawRectangle(dst.x , dst.y , dst.width , dst.height , color);
	//DrawRectangle(attackBox.x * 64.f, attackBox.y * 64.f, attackBox.width * 64.f, attackBox.height * 64.f, color);
}
void SkeletonEnemy::CollisionCheck() {
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		// Player Take Damage Unless player is in deflect
		if (!playerRef->GetHit(pos, 10, currentAttackId))
		{
			health -= 10;
			UpdateAgroSwitch();
			dec = DAMAGED;
			anim.SetAnimation(blockAtlas, 5, false);

		}
	}
}

void SkeletonEnemy::Walk(float dt) {
	dt;
}
void SkeletonEnemy::Attack(float dt) {
	dt;
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{	
	case 11:
		attackBox = { pos.x, pos.y - 1, 2, 2 };
		attackBox.x = (lookRight) ? pos.x - (attackBox.width) : pos.x ;
		CollisionCheck();
		break;

	case 13:
		dec = DECISION::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
		attackTimer = attackCooldown;
		break;
	}
}

void SkeletonEnemy::UpdateAgroSwitch() {

}

bool SkeletonEnemy::GetHit(Vector2 sourcePos, int potentialDamage, int id) {
	if (dec == DAMAGED)
	{
		return false;
	}
	dec = DAMAGED;
	anim.SetAnimation(blockAtlas, 5, false);
	playerRef->LoseAdvantage();
	attackTimer = 0.f;
	/*
	if (id == lastAttackId)
	{
		return false;
	}
	*/
	//UpdateAgroSwitch();
	//pos.x = (sourcePos.x < pos.x) ? pos.x + 2.f : pos.x - 2.f;
	health -= potentialDamage;
	lastAttackId = id;
	return true;
}

void SkeletonEnemy::RenderUI() {

	if (isBoss)
	{
		return;
	}
	Rectangle blackBar{ pos.x * 64.f - 64.f, pos.y * 64.f + 64.f + 16.f , 128.f, 16.f };
	DrawRectangleRec(blackBar, BLACK);


	float margin = 3.f;
	Rectangle remainingHealth = { blackBar.x + margin,blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f};
	float percent = (float)health / (float)maxHealth;
	remainingHealth.width *= percent;

	DrawRectangleRec(remainingHealth, GREEN);
}

void SkeletonEnemy::Reset()
{
	SetIsAlive(true);
	anim.SetAnimation(idleAtlas, 8, false);
	health = maxHealth;
	pos = startPos;
	dec = IDLE;
}
