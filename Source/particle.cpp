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

SnowParticle::SnowParticle()
{
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
			particles[i].pos.y = 0.f;
			timeTillFadeTimer[i] = TIME_TILL_FADE;
			particles[i].size.x = PARTICLE_SIZE;
			particles[i].size.y = PARTICLE_SIZE;
		}
		if (particles[i].pos.x < 0.f)
		{
			particles[i].pos.x = (float)screenWidth;
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



LeafParticle::LeafParticle()
{
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

		
		int randCol = GetRandomValue(1, 3);
		switch (randCol)
		{
		case 1:
			particles[i].col = BROWN;
			break;
		case 2:
			particles[i].col = DARKBROWN;
			break;
		case 3:
			particles[i].col = ORANGE;
			break;
		}
		//particles[i].col.a = (char)GetRandomValue(10, 255);

	}
}

void LeafParticle::Update(float dt)
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
			particles[i].pos.y = 0.f;
			timeTillFadeTimer[i] = TIME_TILL_FADE;
			particles[i].size.x = PARTICLE_SIZE;
			particles[i].size.y = PARTICLE_SIZE;
		}
		if (particles[i].pos.x < 0.f)
		{
			particles[i].pos.x = (float)screenWidth;
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

SwordClashParticle::SwordClashParticle(Vector2 pos, Camera2D ref)
{
}

void SwordClashParticle::Update(float dt)
{
	ParticleEffect::Update(dt);
}

void SwordClashParticle::Render()
{
}

