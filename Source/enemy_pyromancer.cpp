#include "enemy_pyromancer.h"

PyromancerEnemy::~PyromancerEnemy()
{
	for (int i = 0; i < p1TxrAmount; i++)
	{
		UnloadTexture(firstPhaseSprites[i]);
	}
	for (int i = 0; i < p2TxrAmount; i++)
	{
		UnloadTexture(secondPhaseSprites[i]);
	}

}
void PyromancerEnemy::SetTextures(Texture2D p1TxrList[], Texture2D p2TxrList[])
{
	for (int i = 0; i < p1TxrAmount; i++)
	{
		firstPhaseSprites[i] = p1TxrList[i];
	}
	for (int i = 0; i < p2TxrAmount; i++)
	{
		secondPhaseSprites[i] = p2TxrList[i];
	}
}
void PyromancerEnemy::SetAudio(Sound death, Sound init, Sound swing) {
	death;
	init;
	swing;
}
void PyromancerEnemy::Setup() {
	size.x = 80.f * scale;
	size.y = 64.f * scale;

	leftBorder.x = pos.x - 10;
	rightBorder.x = pos.x + 10;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;


	maxHealth = 50;
	health = maxHealth;
}
void PyromancerEnemy::Sense() {
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf((x * x) + (y * y));

	rDist = rightBorder.x - pos.x;
	lDist = pos.x - leftBorder.x;
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
void PyromancerEnemy::Decide() {

	if (inFirstPhase)
	{
		Phase1Decision();
	}
	else
	{
		Phase2Decision();
	}
}
void PyromancerEnemy::Act(float dt) {
	anim.UpdateAnimator(dt);
	hitBox = { pos.x, pos.y - 0.5f , 1.f,1.5f };
	hitBox.x = (lookRight) ? pos.x - 0.0f : pos.x - 1.f;
	oilAmount -= dt * 0.25f;
	attackTimer -= dt;
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::WALK:
		Walk(dt);
		break;
	case DECISION::ATTACK:
		Attack(dt);
		break;
	case DECISION::DAMAGED:
		if (anim.GetCurrentFrame() >= 4)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(firstPhaseSprites[0], 8, true);
			if (health <= 0)
			{
				//PlaySound(deathSound);
				SetIsAlive(false);
				anim.SetAnimation(firstPhaseSprites[2], 8, false);
			}
		}
		break;
	case DECISION::REFILL:
		if (anim.GetCurrentFrame() >= 11)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(firstPhaseSprites[0], 8, true);
			oilAmount = 1.f;
		}
		break;
	default:
		
		break;
	}
}
void PyromancerEnemy::Render() {
	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
	}
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 16.f , size.x, size.y };
	Vector2 origin = {dst.width /2.f, dst.height * 0.75f };

	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	Rectangle testBox{ attackBox.x * 64.f, attackBox.y * 64.f,attackBox.width * 64.f ,attackBox.height * 64.f };
	Color color = YELLOW;
	color.a = 50;
	DrawRectangleRec(testBox, color);
}
void PyromancerEnemy::CollisionCheck() {
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (!playerRef->GetHit(pos, 10, currentAttackId))
		{
			UpdateAgroSwitch();
			if (currentAttackNum != 1 && currentAttackNum != 4)
			{
				health -= 10;
				dec = DAMAGED;
				anim.SetAnimation(firstPhaseSprites[3], 5, false);
			}

		}
	}
}
void PyromancerEnemy::Walk(float dt) {
	if (lookRight)
	{
		pos.x -= dt * speed;
		return;
	}
	else if (!lookRight)
	{

		pos.x += dt * speed;
	}
}
void PyromancerEnemy::Attack(float dt) {
	dt;
	/*
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{
	case 6:
		//PlaySound(swingAttackSound);
		break;
	case 7:

		attackBox = { pos.x, pos.y - 1, 2, 2 };
		attackBox.x = (!lookRight) ? pos.x : pos.x - (attackBox.width);
		CollisionCheck();
		break;
	case 8:

		break;
	case 11:
		dec = DECISION::IDLE;

		break;
	}

	*/
	switch (currentAttackNum)
	{
	case 1:
		OilAttack(dt);
		break;
	case 2:
		SeathAttack(dt);
		break;
	case 3:
		SliceAttack(dt);
		break;
	case 4:
		ThrustAttack(dt);
		break;
	}
}
void PyromancerEnemy::OilAttack(float dt)
{
	// Moves like a jump back
	if (anim.GetCurrentFrame() >= 5 && anim.GetCurrentFrame() <= 10) {
		pos.x += (lookRight) ? 5.f * dt : -5.f * dt;
		AttackCollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 11)
	{
		EndAttack();
	}
}
void PyromancerEnemy::SeathAttack(float dt)
{
	dt;
	if (anim.GetCurrentFrame() == 8)
	{
		AttackCollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 11)
	{
		EndAttack();
	}
}
void PyromancerEnemy::SliceAttack(float dt)
{
	dt;
	if (anim.GetCurrentFrame() == 7)
	{
		pos.x += (lookRight) ? -10.f * dt : 10.f * dt;
		AttackCollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 9)
	{
		EndAttack();
	}
}

void PyromancerEnemy::ThrustAttack(float dt)
{
	// Moves like forward dash
	if (anim.GetCurrentFrame() >= 7) {
		pos.x += (lookRight) ? -20.f * dt : 20.f * dt;

		AttackCollisionCheck();

	}
	if (anim.GetCurrentFrame() >= 11)
	{
		EndAttack();
	}
}

void PyromancerEnemy::AttackCollisionCheck()
{
	attackBox = { pos.x, pos.y - 1, 2, 2 };
	attackBox.x = (!lookRight) ? pos.x : pos.x - (attackBox.width);
	CollisionCheck();
}
void PyromancerEnemy::EndAttack()
{
	attackTimer = attackCooldown;
	dec = DECISION::IDLE;
	anim.SetAnimation(firstPhaseSprites[0], 8, true);
}
void PyromancerEnemy::UpdateAgroSwitch() {

}
bool PyromancerEnemy::GetHit(Vector2 sourcePos, int potentialDamage, int id) {
	sourcePos;
	potentialDamage;
	id;
	return false;
}
void PyromancerEnemy::RenderUI() {
	if (isBoss)
	{
		return;
	}
	Rectangle blackBar{ pos.x * 64.f - 64.f, pos.y * 64.f + 64.f + 16.f , 128.f, 16.f };
	DrawRectangleRec(blackBar, BLACK);

	float margin = 3.f;
	Rectangle remainingHealth = { blackBar.x + margin,blackBar.y + margin, blackBar.width - margin * 2.f, blackBar.height - margin * 2.f };
	float percent = (float)health / (float)maxHealth;
	remainingHealth.width *= percent;

	DrawRectangleRec(remainingHealth, GREEN);

}
void PyromancerEnemy::Reset() {
	SetIsAlive(true);
	anim.SetAnimation(firstPhaseSprites[0], 8, false);
	health = maxHealth;
	pos = startPos;
	dec = DECISION::IDLE;
}

void PyromancerEnemy::Phase1Decision()
{

	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED || dec == DECISION::REFILL)
	{
		return;
	}
	if (oilAmount <= 0.f)
	{
		dec = DECISION::REFILL;
		anim.SetAnimation(firstPhaseSprites[2], 12, false);
		return;
	}
	if (!hasAdvantage)
	{
		dec = DECISION::IDLE;
		return;
	}
	
	if (distance <= 1.5f && attackTimer <= 0.f)
	{
		dec = DECISION::ATTACK;

		currentAttackNum = GetRandomValue(1, 4);
		switch (currentAttackNum)
		{
		case 1:
			anim.SetAnimation(firstPhaseSprites[5], 12, false);
			break;
		case 2:
			anim.SetAnimation(firstPhaseSprites[6], 12, false);
			break;
		case 3:
			anim.SetAnimation(firstPhaseSprites[7], 10, false);
			break;
		case 4:
			anim.SetAnimation(firstPhaseSprites[8], 12, false);
			break;
		}
		
		/*
		PlaySound(initAttackSound);
		switch (currentSlice)
		{
		case 1:
			anim.SetAnimation(attack1Atlas, 12, false);
			currentSlice = 2;
			break;
		case 2:
			anim.SetAnimation(attack2Atlas, 12, false);
			currentSlice = 1;
			break;
		}

		currentAttackId++;
		*/

	}
	else if (distance >= 1.5f && lookRight && lDist > 1.f || distance >= 1.5f && !lookRight && rDist > 1.f)
	{
		dec = DECISION::WALK;
		anim.SetAnimation(firstPhaseSprites[1], 8, true);
	}
	else if (dec != IDLE)
	{
		dec = DECISION::IDLE;
		anim.SetAnimation(firstPhaseSprites[0], 8, true);
	}
}

void PyromancerEnemy::Phase2Decision()
{
}
