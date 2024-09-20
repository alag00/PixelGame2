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
	sounds[0] = death;
	sounds[1] = init;
	sounds[2] = swing;
}
void PyromancerEnemy::Setup() {
	size.x = 80.f * scale;
	size.y = 64.f * scale;

	leftBorder.x = pos.x - 15;
	rightBorder.x = pos.x + 15;

	leftBorder.y = pos.y;
	rightBorder.y = pos.y;


	maxHealth = 100;
	health = maxHealth;
	anim.SetAnimation(firstPhaseSprites[0], 8, true);
	for (int i = 0; i < 3; i++)
	{
		fireBalls[i].SetTxr(secondPhaseSprites[8]);
		fireBalls[i].SetRef(*playerRef);
	}
}
void PyromancerEnemy::Sense() {
	float x = pos.x - playerRef->GetCenter().x;
	float y = pos.y - playerRef->GetCenter().y;
	distance = sqrtf((x * x) + (y * y));

	rDist = rightBorder.x - pos.x;
	lDist = pos.x - leftBorder.x;
	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED || dec == DECISION::TRANSFORMATION)
	{
		return;
	}
	if (lookLeft && pos.x < playerRef->GetCenter().x || !lookLeft && pos.x > playerRef->GetCenter().x)
	{
		lookLeft = !lookLeft;
		anim.FlipAnimationHorizontal();
		pos.x += (lookLeft) ? -1.f : 1.f ;
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
void PyromancerEnemy::Phase1Decision()
{

	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED || dec == DECISION::REFILL || dec == DECISION::TRANSFORMATION)
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
		PlaySound(sounds[1]);
		currentAttackNum = GetRandomValue(1, 100);

		if (currentAttackNum > 0 && currentAttackNum <= 35)
		{
			currentAttackNum = 4;
		}
		else if (currentAttackNum > 35 && currentAttackNum <= 70)
		{
			currentAttackNum = 3;
		}
		else if (currentAttackNum > 70 && currentAttackNum <= 90)
		{
			currentAttackNum = 2;
		}
		else if (currentAttackNum > 90 && currentAttackNum <= 100)
		{
			currentAttackNum = 1;
		}

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

		

	}
	else if (distance >= 1.5f && lookLeft && lDist > 1.f || distance >= 1.5f && !lookLeft && rDist > 1.f)
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

	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED || dec == DECISION::REFILL)
	{
		return;
	}

	if (!hasAdvantage)
	{
		dec = DECISION::IDLE;
		return;
	}

	if (distance <= 4.f && attackTimer <= 0.f)
	{
		dec = DECISION::ATTACK;
		PlaySound(sounds[1]);
		currentAttackNum = GetRandomValue(1, 100);

		if (currentAttackNum > 0 && currentAttackNum <= 35)
		{
			currentAttackNum = 6;
		}
		else if (currentAttackNum > 35 && currentAttackNum <= 70)
		{
			currentAttackNum = 5;
		}
		else if (currentAttackNum > 70 && currentAttackNum <= 90)
		{
			currentAttackNum = 7;
		}
		else if (currentAttackNum > 90 && currentAttackNum <= 100)
		{
			currentAttackNum = 8;
		}

		switch (currentAttackNum)
		{
		case 5:
			anim.SetAnimation(secondPhaseSprites[3], 10, false);
			break;
		case 6:
			anim.SetAnimation(secondPhaseSprites[4], 12, false);
			break;
		case 7:
			anim.SetAnimation(secondPhaseSprites[5], 6, false);
			attackStage = 1;
			break;
		case 8:
			anim.SetAnimation(secondPhaseSprites[5], 6, false);
			attackStage = 1;
			break;
		}


	}
	else if (distance >= 4.f && lookLeft && lDist > 1.f || distance >= 1.5f && !lookLeft && rDist > 1.f)
	{
		dec = DECISION::WALK;
		anim.SetAnimation(secondPhaseSprites[1], 8, true);
	}
	else if (dec != IDLE)
	{
		dec = DECISION::IDLE;
		anim.SetAnimation(secondPhaseSprites[0], 8, true);
	}
}


void PyromancerEnemy::Act(float dt) {
	if (dec == TRANSFORMATION && deadPause > 0.f && anim.GetCurrentFrame() == 4)
	{
		
	}
	else
	{
		anim.UpdateAnimator(dt);
	}
	hitBox = { pos.x, pos.y - 0.5f , 1.f,1.5f };
	hitBox.x = (lookLeft) ? pos.x - 0.0f : pos.x - 1.f;
	oilAmount -= dt * 0.25f;
	attackTimer -= dt;
	for (int i = 0; i < 3; i++)
	{
		fireBalls[i].Update(dt);
	}
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::WALK:
		Move(dt);
		break;
	case DECISION::ATTACK:
		Attack(dt);
		break;
	case DECISION::DAMAGED:
		Damaged(dt);
	
		break;
	case DECISION::REFILL:
		if (anim.GetCurrentFrame() >= 11)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(firstPhaseSprites[0], 8, true);
			oilAmount = 1.f;
		}
		break;
	case DECISION::TRANSFORMATION:
		if (anim.GetCurrentFrame() == 4)
		{
			deadPause -= dt;
		}
		if (anim.GetCurrentFrame() >= 19)
		{
			inFirstPhase = false;
			dec = DECISION::IDLE;
			health = maxHealth;
		}
		break;
	default:
		
		break;
	}
}
void PyromancerEnemy::Render() {

	Rectangle dst = { pos.x * 64.f , pos.y * 64.f + 16.f , size.x, size.y };
	Vector2 origin = {dst.width /2.f, dst.height * 0.75f };

	Color color = (dec != DAMAGED) ? WHITE : RED;
	anim.DrawAnimationPro(dst, origin, 0.f, color);

	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
		return;
	}
	

	for (int i = 0; i < 3; i++)
	{
		fireBalls[i].Render();
	}
}
void PyromancerEnemy::Move(float dt) {

	float currentSpeed = (inFirstPhase) ? p1Speed : p2Speed;
	if (lookLeft)
	{
		pos.x -= dt * currentSpeed;
		return;
	}
	else if (!lookLeft)
	{

		pos.x += dt * currentSpeed;
	}
}


void PyromancerEnemy::Attack(float dt) {
	dt;

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
	case 5:
		FlameSlice(dt);
		break;
	case 6:
		FlameThrust(dt);
		break;
	case 7:
		FlameRangedAttack(dt);
		break;
	case 8:
		FlameFlyAttack(dt);
		break;
	}
}
void PyromancerEnemy::OilAttack(float dt)
{
	if (anim.GetCurrentFrame() == 5)
	{
		PlaySound(sounds[2]);
	}
	if (anim.GetCurrentFrame() >= 5 && anim.GetCurrentFrame() <= 10) {
		pos.x += (lookLeft) ? 5.f * dt : -5.f * dt;
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
		PlaySound(sounds[2]);
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
		pos.x += (lookLeft) ? -10.f * dt : 10.f * dt;
		AttackCollisionCheck();
		PlaySound(sounds[2]);
	}
	if (anim.GetCurrentFrame() >= 9)
	{
		EndAttack();
	}
}
void PyromancerEnemy::ThrustAttack(float dt)
{
	if (anim.GetCurrentFrame() == 7)
	{
		PlaySound(sounds[2]);
	}
	if (anim.GetCurrentFrame() >= 7) {
		pos.x += (lookLeft) ? -20.f * dt : 20.f * dt;

		AttackCollisionCheck();

	}
	if (anim.GetCurrentFrame() >= 11)
	{
		EndAttack();
	}
}

void PyromancerEnemy::FlameSlice(float dt)
{
	dt; 
	pos.x += (lookLeft) ? -p1Speed * dt : p1Speed * dt;
	if (anim.GetCurrentFrame() == 7)
	{
		PlaySound(sounds[2]);
		pos.x += (lookLeft) ? -p2Speed * dt : p2Speed * dt;
		AttackCollisionCheck();
	}
	if (anim.GetCurrentFrame() >= 9)
	{
		EndAttack();
	}
}
void PyromancerEnemy::FlameThrust(float dt)
{
	if (anim.GetCurrentFrame() == 7)
	{
		PlaySound(sounds[2]);
	}
	if (anim.GetCurrentFrame() >= 7) {
		pos.x += (lookLeft) ? -20.f * dt : 20.f * dt;

		AttackCollisionCheck();

	}
	if (anim.GetCurrentFrame() >= 11)
	{
		EndAttack();
	}
}
void PyromancerEnemy::FlameRangedAttack(float dt)
{

	dt;
	int currentFrame = anim.GetCurrentFrame();
	switch (attackStage)
	{
	case 1:
		push = true;
		AttackCollisionCheck();
		if (currentFrame >= 5)
		{
			push = false;
			attackStage = 2;
			anim.SetAnimation(secondPhaseSprites[6], 4, true);
		}
		break;
	case 2:
		pos.x += (lookLeft) ? p2Speed * dt : -p2Speed * dt;
		if (distance >= 10.5f && lookLeft && lDist > 1.f || distance >= 10.5f && !lookLeft && rDist > 1.f)
		{
			PlaySound(sounds[2]);
			attackStage = 3;
			anim.SetAnimation(secondPhaseSprites[7], 14, false);
		}
	
		break;
	case 3:
		switch (currentFrame)
		{
		case 2:
			fireBalls[0].Setup(pos, playerRef->GetCenter(), lookLeft);
			break;
		case 7:
			fireBalls[1].Setup(pos, playerRef->GetCenter(), lookLeft);
			break;
		case 11:
			fireBalls[2].Setup(pos, playerRef->GetCenter(), lookLeft);
			break;
		case 13:
			EndAttack();
			break;
		}
		break;
	}
	
}
void PyromancerEnemy::FlameFlyAttack(float dt)
{

	dt;
	int currentFrame = anim.GetCurrentFrame();
	switch (attackStage)
	{
	case 1:
		push = true;
		AttackCollisionCheck();
		if (currentFrame >= 5)
		{
			push = false;
			attackStage = 2;
			anim.SetAnimation(secondPhaseSprites[6], 4, true);
		}
		break;
	case 2:
		pos.x += (lookLeft) ? p2Speed * dt : -p2Speed * dt;
		pos.y += (p2Speed / 2.f) * -dt;
		flyProgress += dt * 2.f;

		if (flyProgress >= 1.f)
		{
			attackStage = 3;
			anim.SetAnimation(secondPhaseSprites[9], 4, true);
			flyProgress = 0.f;
			PlaySound(sounds[2]);
		}
		
		break;
	case 3:
		pos.x += (lookLeft) ? 1.5f * -p2Speed * dt : 1.5f*p2Speed * dt;
		pos.y += (p2Speed / 2.f) * dt;
		if (pos.y > startPos.y)
		{
			pos.y = startPos.y;
		}
		flyProgress += dt ;
		AttackCollisionCheck();
		if (flyProgress >= 1.f)
		{
			flyProgress = 0.f;
			EndAttack();
		}
		
		break;
	}
}

void PyromancerEnemy::CollisionCheck() {
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		int damage = (push) ? 0 : ATTACK_DAMAGE;
		if (!playerRef->GetHit(pos, damage))
		{
			UpdateAgroSwitch();
			if (currentAttackNum != 1)
			{
				health -= DEFLECTED_DAMAGE;
				dec = DAMAGED;
				if (inFirstPhase)
				{

				anim.SetAnimation(firstPhaseSprites[3], 5, false);
				}
				else
				{
					anim.SetAnimation(secondPhaseSprites[2], 7, false);
				}
			}
			pos.y = startPos.y;

		}
	}
}
void PyromancerEnemy::AttackCollisionCheck()
{
	attackBox = { pos.x, pos.y - 1, 2, 2 };
	attackBox.x = (!lookLeft) ? pos.x : pos.x - (attackBox.width);
	CollisionCheck();
}
void PyromancerEnemy::EndAttack()
{
	attackTimer = attackCooldown;
	dec = DECISION::IDLE;
	if (inFirstPhase)
	{

		anim.SetAnimation(firstPhaseSprites[0], 8, true);
	}
	else
	{
		anim.SetAnimation(secondPhaseSprites[0], 8, true);
	}
}


void PyromancerEnemy::UpdateAgroSwitch() {

}
void PyromancerEnemy::Damaged(float dt)
{
	dt;
	if (inFirstPhase)
	{
		if (anim.GetCurrentFrame() >= 4)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(firstPhaseSprites[0], 8, true);
			if (health <= 0)
			{
				PlaySound(sounds[0]);
				dec = DECISION::TRANSFORMATION;
				anim.SetAnimation(firstPhaseSprites[9], 20, false);
			}
		}
	}
	else
	{
		if (anim.GetCurrentFrame() >= 6)
		{
			dec = DECISION::IDLE;
			anim.SetAnimation(secondPhaseSprites[0], 8, true);
			if (health <= 0)
			{
				PlaySound(sounds[0]);
				SetIsAlive(false);
				anim.SetAnimation(secondPhaseSprites[10], 12, false);
			}
		}
	}
}
bool PyromancerEnemy::GetHit(Vector2 sourcePos, int potentialDamage) {
	if (health <= 0)
	{
		return false;
	}
	sourcePos;
	potentialDamage;

	health -= potentialDamage;
	if (health <= 0)
	{
		dec = DECISION::DAMAGED;
		if (inFirstPhase)
		{
			anim.SetAnimation(firstPhaseSprites[3], 5, false);
		}
		else
		{
			anim.SetAnimation(secondPhaseSprites[2], 7, false);
		}
	}
	pos.y = startPos.y;
	
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
	if (isBoss && !IsAlive())
	{
		return;
	}

	inFirstPhase = true;
	SetIsAlive(true);
	anim.SetAnimation(firstPhaseSprites[0], 8, false);
	health = maxHealth;
	pos = startPos;
	dec = DECISION::IDLE;
	for (int i = 0; i < 3; i++)
	{
		fireBalls[i].Reset();
	}
}



void FireBall::SetRef(Entity& ref)
{
	playerRef = &ref;
}
void FireBall::SetTxr(Texture2D txr)
{
	anim.SetAnimation(txr, 4, true);
	size.x = 32.f * scale;
	size.y = 16.f * scale;
}
void FireBall::Setup(Vector2 newPos, Vector2 newTarget, bool left)
{
	pos = newPos;
	timeAlive = 2.f;

	float x = pos.x - newTarget.x;
	float y = pos.y - newTarget.y;
	float mag = sqrtf(x * x + y * y);

	vel.x = -x / mag;
	vel.y = -y / mag;

	if (lookLeft != left)
	{
		anim.FlipAnimationHorizontal();
		lookLeft = left;
	}
}
void FireBall::Update(float dt)
{
	if (timeAlive <= 0.f)
	{
		return;
	}
	anim.UpdateAnimator(dt);
	pos.x += vel.x * speed* dt;
	pos.y += vel.y * speed* dt;

	Rectangle bulletBox{ pos.x, pos.y, 2.f, 1.f };
	if (CheckCollisionRecs(playerRef->hitBox, bulletBox))
	{
		playerRef->GetHit(pos, ATTACK_DAMAGE);
		timeAlive = 0.f;
	}
}
void FireBall::Render()
{
	if (timeAlive <= 0.f)
	{
		return;
	}
	Rectangle dst = { pos.x*64.f, pos.y *64.f ,size.x,size.y  };
	Vector2 origin = { 0.f,0.f };
	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	
}
void FireBall::Reset()
{
	timeAlive = 0.f;
}