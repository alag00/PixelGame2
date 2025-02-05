#include "enemy_necromancer.h"

NecromancerEnemy::~NecromancerEnemy() 
{ 
	playerRef = nullptr; 

	UnloadTexture(idleAtlas);
	UnloadTexture(deathAtlas);
	UnloadTexture(meleeAttackAtlas);
	UnloadTexture(rangedAttackAtlas);

	UnloadTexture(blockAtlas);
	UnloadTexture(pushAtlas);
	UnloadTexture(projectileAtlas);

	UnloadSound(deathSound);
	UnloadSound(initAttackSound);
	UnloadSound(swingAttackSound);
	
}
void NecromancerEnemy::Setup()
{
	size.x = 144.f * scale;
	size.y = 112.f * scale;

	anim.SetAnimation(idleAtlas, 8, true);

	maxHealth = 100;
	health = maxHealth;

	for (int i = 0; i < projAmount; i++)
	{
		int dir = (i % 2 == 0) ? 1 : -1;
		projList[i].Setup(*playerRef, dir, projectileAtlas, pos);
	}
}
void NecromancerEnemy::SetTextures(Texture2D idleTxr, Texture2D deathTxr, Texture2D meleeTxr, Texture2D rangedTxr, Texture2D blockTxr, Texture2D pushTxr, Texture2D projTxr)
{
	idleAtlas = idleTxr;
	deathAtlas = deathTxr;
	meleeAttackAtlas = meleeTxr;
	rangedAttackAtlas = rangedTxr;

	blockAtlas = blockTxr;
	pushAtlas = pushTxr;
	projectileAtlas = projTxr;
	
}

void NecromancerEnemy::SetAudio(Sound death, Sound init, Sound swing)
{
	deathSound = death;
	initAttackSound = init;
	swingAttackSound = swing;
}
void NecromancerEnemy::Sense()
{
	float x = (pos.x + 0.5f) - playerRef->GetCenter().x;
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
void NecromancerEnemy::Decide() {
	if (dec == DECISION::ATTACK || dec == DECISION::DAMAGED)
	{
		return;
	}
	if (distance <= 1.f)
	{
		dec = DECISION::PUSH;
		anim.SetAnimation(pushAtlas, 8, false);

	}
	else if (distance <= 4.f && attackTimer < 0.f)
	{
		PlaySound(initAttackSound);
		dec = DECISION::ATTACK;
		anim.SetAnimation(meleeAttackAtlas, 14, false);

	}
	else if (distance <= 20.f && attackTimer < 0.f)
	{
		
		dec = DECISION::RANGED;
		anim.SetAnimation(rangedAttackAtlas, 12, false);

	}
	else
	{
		dec = DECISION::IDLE;
	}
}
void NecromancerEnemy::Act(float dt) {
	anim.UpdateAnimator(dt);
	attackTimer -= dt;
	hitBox = { pos.x -0.5f , pos.y -2  , 2.f,3.f };
	damagedTimer -= dt;
	UpdateProj(dt);
	switch (dec)
	{
	case DECISION::IDLE:
		break;
	case DECISION::ATTACK:
		Attack();
		break;
	case DECISION::RANGED:
		RangedAttack();
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
	case DECISION::PUSH:
		Push();
		break;
	}
}

void NecromancerEnemy::UpdateProj(float dt)
{
	for (int i = 0; i < projAmount; i++)
	{
		if (projList[i].IsAlive())
		{
			projList[i].Update(dt);
		}
	}
	
}

void NecromancerEnemy::Render() {
	
	Rectangle dst = { pos.x * 64.f , pos.y * 64.f , size.x, size.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f };
	dst.x = (lookRight) ? dst.x - 64.f : dst.x;
	Color color = (dec == DAMAGED || damagedTimer > 0.f) ? RED : WHITE;
	anim.DrawAnimationPro(dst, origin, 0.f, color);

	if (!IsAlive())
	{
		anim.UpdateAnimator(GetFrameTime());
		return;
	}

	for (int i = 0; i < projAmount; i++)
	{
		if (projList[i].IsAlive())
		{
			projList[i].Render();
		}
	}
	
}
void NecromancerEnemy::CollisionCheck() {
	if (CheckCollisionRecs(playerRef->hitBox, attackBox))
	{
		if (!playerRef->GetHit(pos, ATTACK_DAMAGE))
		{
			health -= DEFLECTED_DAMAGE;
			
			dec = DAMAGED;
			anim.SetAnimation(blockAtlas, 5, false);

		}
	}
}


void NecromancerEnemy::Attack() {
	
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{
	case 6:
		PlaySound(swingAttackSound);
		break;
	case 7:
		attackBox = { pos.x, pos.y - 3, 4, 4 };
		attackBox.x = (lookRight) ? pos.x - (attackBox.width) + 1 : pos.x;
		CollisionCheck();
		break;

	case 13:
		dec = DECISION::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
		attackTimer = attackCooldown;
		break;
	}
}

void NecromancerEnemy::RangedAttack() {
	
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{

	case 11:
		for (int i = 0; i < projAmount; i++)
		{
			projList[i].Activate(pos);
		}
		

		dec = DECISION::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
		attackTimer = attackCooldown;
		break;
	}
}

void NecromancerEnemy::Push()
{
	int currentFrame = anim.GetCurrentFrame();
	switch (currentFrame)
	{
	case 3:
		attackBox = { pos.x -1, pos.y - 3, 4, 4 };
		CollisionCheck();
		break;

	case 5:
		dec = DECISION::IDLE;
		anim.SetAnimation(idleAtlas, 8, true);
		break;
	}
}


bool NecromancerEnemy::GetHit(Vector2 sourcePos, int potentialDamage) {
	if (dec == DAMAGED || !IsAlive())
	{
		return false;
	}
	(void)sourcePos;
	
	damagedTimer = 0.1f;
	health -= potentialDamage;
	if (health <= 0)
	{
		dec = DAMAGED;
		anim.SetAnimation(blockAtlas, 5, false);
	}
	return true;
}

void NecromancerEnemy::RenderUI() {
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

void NecromancerEnemy::Reset()
{
	if (isBoss && !IsAlive())
	{
		return;
	}
	SetIsAlive(true);
	anim.SetAnimation(idleAtlas, 8, false);
	health = maxHealth;
	pos = startPos;
	dec = IDLE;
}



void Projectiles::Setup(Entity& ref, int direction, Texture2D txr, Vector2 newPos)
{
	playerRef = &ref;
	dir = direction;
	size.x = 64.f * scale;
	size.y = 32.f * scale;

	pos = newPos;
	pos.y += 0.5f;

	anim.SetAnimation(txr, 4, true);

	if (dir == 1)
	{
		anim.FlipAnimationHorizontal();
	}
}

void Projectiles::Activate(Vector2 newPos)
{
	timeAlive = 2.f;
	pos = newPos;
	pos.y += 0.5f;
}

void Projectiles::Update(float dt)
{
	anim.UpdateAnimator(dt);
	CollisionCheck();
	timeAlive -= dt;
	switch (dir)
	{
	case -1:
		pos.x -= dt * 10.f;
		break;
	case 1:
		pos.x += dt * 10.f;
		break;
	}
}
void Projectiles::CollisionCheck()
{
	hitBox = { pos.x + dir , pos.y -0.5f  , 2.f, 1.f };
	hitBox.x = (dir == 1) ? pos.x : hitBox.x;
	if (CheckCollisionRecs(playerRef->hitBox, hitBox))
	{

		if (!playerRef->GetHit(pos, ATTACK_DAMAGE))
		{
			
		}
		timeAlive = 0.f;
	}
}
void Projectiles::Render() 
{
	Rectangle dst = { pos.x * config.tileSize , pos.y * config.tileSize , size.x, size.y };
	Vector2 origin = { dst.width * 0.35f , dst.height * 0.75f };

	anim.DrawAnimationPro(dst, origin, 0.f, WHITE);

	
}
bool Projectiles::IsAlive() 
{
	if (timeAlive < 0.f)
	{
		return false;
	}
	return true;
}