#include "particle.h"

void ParticleEffect::Update(float dt)
{
	if (!loop)
	{
		timeAlive -= dt;
	}
	if (timeAlive < 0.f)
	{
		activated = false;
	}
}

SnowParticle::SnowParticle(Camera2D& ref)
{
	camRef = &ref;

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x = (float)GetRandomValue(0, screenWidth);
		particles[i].pos.y = (float)GetRandomValue(-screenHeight / 2, screenHeight / 2);

		particles[i].vel.x = WIND_SPEED;
		particles[i].vel.y = (float)GetRandomValue(FALL_SPEED_MIN, FALL_SPEED_MAX);

		particles[i].size.x = PARTICLE_SIZE;
		particles[i].size.y = PARTICLE_SIZE;

		timeTillFadeTimer[i] = (float)GetRandomValue(0, ((int)TIME_TILL_FADE * ONE_DECIMAL_FLOAT_CONVERT)) / (float)ONE_DECIMAL_FLOAT_CONVERT;
		//particles[i].col.a = (char)GetRandomValue(10, 255);
		
	}
}

void SnowParticle::Update(float dt)
{
	//ParticleEffect::Update(dt);
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x += particles[i].vel.x * dt;
		particles[i].pos.y += particles[i].vel.y * dt;
	
		timeTillFadeTimer[i] -= dt;


		if (timeTillFadeTimer[i] <= 0.f)
		{
			particles[i].col.a--; //-= (char)GetRandomValue(0, 2);
			particles[i].size.x -= dt;
			particles[i].size.y = particles[i].size.x;
		}

		if (particles[i].col.a <= 2)
		{
			particles[i].col.a = 255;
			particles[i].pos.y = camRef->target.y - camRef->offset.y;
			timeTillFadeTimer[i] = TIME_TILL_FADE;
			particles[i].size.x = PARTICLE_SIZE;
			particles[i].size.y = PARTICLE_SIZE;
		}
		if (particles[i].pos.x < camRef->target.x - camRef->offset.x)
		{
			particles[i].pos.x = camRef->target.x - camRef->offset.x + (float)screenWidth;
		}
		else if (particles[i].pos.x > camRef->target.x - camRef->offset.x + (float)screenWidth)
		{
			particles[i].pos.x = camRef->target.x - camRef->offset.x;
		}
	}

}
void SnowParticle::Render()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		DrawRectangle((int)particles[i].pos.x, (int)particles[i].pos.y, (int)particles[i].size.x, (int)particles[i].size.x, particles[i].col);
	}
}



LeafParticle::LeafParticle(Camera2D& ref)
{
	camRef = &ref;

	screenWidth = GetScreenWidth();
	screenHeight = GetScreenHeight();

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x = (float)GetRandomValue(0, screenWidth);
		particles[i].pos.y = (float)GetRandomValue(-screenHeight / 2, screenHeight / 2);

		particles[i].vel.x = WIND_SPEED;
		particles[i].vel.y = (float)GetRandomValue(FALL_SPEED_MIN, FALL_SPEED_MAX);

		particles[i].size.x = PARTICLE_SIZE;
		particles[i].size.y = PARTICLE_SIZE;

		timeTillFadeTimer[i] = (float)GetRandomValue(0, ((int)TIME_TILL_FADE * ONE_DECIMAL_FLOAT_CONVERT)) / (float)ONE_DECIMAL_FLOAT_CONVERT;
		//particles[i].col.a = (char)GetRandomValue(10, 255);

		int randNum = GetRandomValue(1, 3);
		switch (randNum)
		{
		case 1:
			particles[i].col = col1;
			break;
		case 2:
			particles[i].col = col2;
			break;
		case 3:
			particles[i].col = col3;
			break;
		}
	}
}

void LeafParticle::Update(float dt)
{
	//ParticleEffect::Update(dt);
	progress += dt;
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x += particles[i].vel.x * dt;
		particles[i].pos.y += particles[i].vel.y * dt;

		
		particles[i].vel.x = cos(progress) * 100.f;

		timeTillFadeTimer[i] -= dt;


		if (timeTillFadeTimer[i] <= 0.f)
		{
			particles[i].col.a--; //-= (char)GetRandomValue(0, 2);
			particles[i].size.x -= dt;
			particles[i].size.y = particles[i].size.x;
		}

		if (particles[i].col.a <= 2)
		{
			particles[i].col.a = 255;
			particles[i].pos.y = camRef->target.y - camRef->offset.y;
			timeTillFadeTimer[i] = TIME_TILL_FADE;
			particles[i].size.x = PARTICLE_SIZE;
			particles[i].size.y = PARTICLE_SIZE;
		}
		if (particles[i].pos.x < camRef->target.x - camRef->offset.x)
		{
			particles[i].pos.x = camRef->target.x - camRef->offset.x + (float)screenWidth;
		}
		else if (particles[i].pos.x > camRef->target.x - camRef->offset.x + (float)screenWidth)
		{
			particles[i].pos.x = camRef->target.x - camRef->offset.x;
		}
	}

}
void LeafParticle::Render()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		DrawRectangle((int)particles[i].pos.x, (int)particles[i].pos.y, (int)particles[i].size.x, (int)particles[i].size.x, particles[i].col);
	}
}

SwordClashParticle::SwordClashParticle(Vector2 pos, Camera2D& ref)
{
	position = pos;
	camRef = &ref;
	SetTimeAlive(TIME);

	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos = position;
		particles[i].vel.x = static_cast<float>(GetRandomValue(SPEED_MIN, SPEED_MAX) / CONVERTER);
		particles[i].vel.y = static_cast<float>(GetRandomValue(SPEED_MIN, SPEED_MAX) / CONVERTER);
		if (particles[i].vel.x == 0.f && particles[i].vel.y == 0)
		{
			particles[i].vel.x = static_cast<float>((SPEED_MIN / 2) / CONVERTER);
			particles[i].vel.y = static_cast<float>((SPEED_MIN / 2) / CONVERTER);
		}
		particles[i].size = { PARTICLE_SIZE, PARTICLE_SIZE };
		particles[i].col = ORANGE;
	}
}

void SwordClashParticle::Update(float dt)
{
	ParticleEffect::Update(dt);
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x += particles[i].vel.x * dt;
		particles[i].pos.y += particles[i].vel.y * dt;

		float procent = GetTimeAlive() / TIME;
		particles[i].col.a = (char)std::lerp(1, 255, procent);
		//particles[i].col.a--;
		particles[i].col.g = (char)std::lerp(160, 255, procent);
	}
}

void SwordClashParticle::Render()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		DrawRectangle(static_cast<int>(particles[i].pos.x * TILE_SIZE), 
			static_cast<int>(particles[i].pos.y * TILE_SIZE),
			static_cast<int>(particles[i].size.x),
			static_cast<int>(particles[i].size.y),
			particles[i].col);
	}
}

SteamParticle::SteamParticle(Vector2 pos, Vector2 vel, Camera2D& ref)
{
	position = pos;
	//velocity = vel;
	camRef = &ref;
	SetTimeAlive(TIME);

	vel.x /= BONUS_VELOCITY_REDUCTION;
	vel.y /= BONUS_VELOCITY_REDUCTION;

	float randOffsetX = 0.f;
	//float randOffsetY = 0.f;
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		randOffsetX = (float)GetRandomValue(-1, 1) / 10.f;
		//randOffsetY = (float)GetRandomValue(-1, 1) / 10.f;
		particles[i].pos = position;// {position.x + randOffsetX, position.y + randOffsetY};
		particles[i].vel.y = SPEED + randOffsetX + vel.y;
		particles[i].vel.x = randOffsetX + vel.x;
		
	}
}

void SteamParticle::Update(float dt)
{
	ParticleEffect::Update(dt);
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		particles[i].pos.x += particles[i].vel.x * dt;
		particles[i].pos.y += particles[i].vel.y * dt;

		float procent = GetTimeAlive() / TIME;
		particles[i].col.a = (char)std::lerp(1, 255, procent);
		particles[i].size.x = (float)std::lerp(MAX_SIZE, MIN_SIZE, procent);
		particles[i].size.y = (float)std::lerp(MAX_SIZE, MIN_SIZE, procent);
	}
}

void SteamParticle::Render()
{
	for (int i = 0; i < PARTICLE_NUM; i++)
	{
		DrawRectangle(static_cast<int>(particles[i].pos.x * TILE_SIZE),
			static_cast<int>(particles[i].pos.y * TILE_SIZE),
			static_cast<int>(particles[i].size.x),
			static_cast<int>(particles[i].size.y),
			particles[i].col);
	}
}
