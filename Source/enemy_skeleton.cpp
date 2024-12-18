#include "enemy_skeleton.h"

SkeletonEnemy::~SkeletonEnemy() 
{ 
	playerRef = nullptr;

	UnloadTexture(idleAtlas);
	UnloadTexture(deathAtlas);
	UnloadTexture(attackAtlas);
	UnloadTexture(blockAtlas);

	UnloadSound(deathSound);
	UnloadSound(initAttackSound);
	UnloadSound(swingAttackSound);
}

void SkeletonEnemy::SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D attackTxr, Texture2D blockTxr)
{
	idleAtlas = idleTxr;
	deathAtlas = deathTxr;
	attackAtlas = attackTxr;
	blockAtlas = blockTxr;
}

void SkeletonEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	deathSound = death;
	initAttackSound = init;
	swingAttackSound = swing;
}

void SkeletonEnemy::Setup()
{
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
	if (lookRight && pos.x < playerRef->GetCenter().x || !lookRight && pos.x > playerRef->GetCenter().x)
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
		PlaySound(initAttackSound);

	}
	else
	{
		dec = DECISION::IDLE;
	
	}
}
void SkeletonEnemy::Act(float dt) {
	anim.UpdateAnimator(dt);
	attackTimer -= dt;
	hitBox = { pos.x, pos.y - 1.f , 1.5f,2.f };
	hitBox.x = (lookRight) ? pos.x - 1.f : pos.x - 0.5f;
	damagedTimer -= dt;
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
				PlaySound(deathSound);
				SetIsAlive(false);
				anim.SetAnimation(deathAtlas, 8, false);
			}
		}
		break;
	}
}

void SkeletonEnemy::Render() {

	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
	}
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 64.f , size.x, size.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f};
	dst.x = (lookRight) ? dst.x - 64.f : dst.x;
	Color color = (dec == DAMAGED || damagedTimer > 0.f) ? RED : WHITE;
	anim.DrawAnimationPro(dst, origin, 0.f, color);

	
}
void SkeletonEnemy::CollisionCheck() {
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (!playerRef->GetHit(pos, ATTACK_DAMAGE))
		{
			health -= DEFLECTED_DAMAGE;
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
	case 9:
		PlaySound(swingAttackSound);
		break;
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

bool SkeletonEnemy::GetHit(Vector2 sourcePos, int potentialDamage) {
	if (dec == DAMAGED)
	{
		return false;
	}
	(void)sourcePos;
	
	
	attackTimer = 0.f;
	damagedTimer = 0.1f;
	health -= potentialDamage;
	if (health <= 0)
	{

		dec = DAMAGED;
		anim.SetAnimation(blockAtlas, 5, false);
	}
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
