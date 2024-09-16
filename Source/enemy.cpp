#include "enemy.h"




void Enemy::Update(float dt)
{
	if (isBoss && !active)
	{
		return;
	}
	timer += dt;
	if (timer >= refreshRate)
	{
		timer = 0.f;
		Sense();
		Decide();
	}
	Act(dt);
}

