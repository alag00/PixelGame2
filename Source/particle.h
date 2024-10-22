#pragma once
#include "raylib.h"
#include <cmath>
struct Particle
{
	Vector2 pos = {0.f,0.f};
	Vector2 vel = { 0.f,0.f };
	Vector2 size = {0.f,0.f};
	Color col = WHITE;
};

class ParticleEffect
{
private:
	float timeAlive = 1.f;
	bool loop = false;
	bool activated = true;
public:
	virtual void Update(float dt);
	virtual void Render(){};
	void SetTimeAlive(float time) { timeAlive = time; }
	float GetTimeAlive() { return timeAlive; }
	bool IsActivated() { return activated; }
};

class SnowParticle : public ParticleEffect
{
private:
	Camera2D* camRef = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
	const float TIME = 2.f; // Loop
	const static int PARTICLE_NUM = 20;
	Particle particles[PARTICLE_NUM]{0.f,0.f,0.f,0.f};
	float timeTillFadeTimer[PARTICLE_NUM] = { 0.f };
	const float TIME_TILL_FADE = 6.f;
	const int ONE_DECIMAL_FLOAT_CONVERT = 10;
	const int FALL_SPEED_MIN = 50;
	const int FALL_SPEED_MAX = 60;
	const float WIND_SPEED = -10.f;
	const float PARTICLE_SIZE = 4.f;
public:
	SnowParticle( Camera2D& ref);
	void Update(float dt) override;
	void Render() override;
};

class LeafParticle : public ParticleEffect
{
private:
	Camera2D* camRef = nullptr;
	int screenWidth = 0;
	int screenHeight = 0;
	const float TIME = 2.f; // Loop
	const static int PARTICLE_NUM = 20;
	Particle particles[PARTICLE_NUM]{ 0.f,0.f,0.f,0.f };
	float timeTillFadeTimer[PARTICLE_NUM] = { 0.f };
	const float TIME_TILL_FADE = 6.f;
	const int ONE_DECIMAL_FLOAT_CONVERT = 10;
	const int FALL_SPEED_MIN = 50;
	const int FALL_SPEED_MAX = 60;
	const float WIND_SPEED = 10.f;
	const float PARTICLE_SIZE = 8.f;

	float progress = 0.f;
	
	const Color col1 = ORANGE;//{128, 91, 51, 255};
	const Color col2 =  {163, 111, 55, 255};
	const Color col3 = {202, 135, 62, 255};
public:
	LeafParticle(Camera2D& ref);
	void Update(float dt) override;
	void Render() override;
};

class SwordClashParticle : public ParticleEffect
{
private:
	Camera2D* camRef = nullptr;
	const float TIME = 0.5f;
	const static int PARTICLE_NUM = 20;
	Particle particles[PARTICLE_NUM]{ 0.f,0.f,0.f,0.f };
	Vector2 position = { 0.f,0.f };

	const int SPEED_MIN = -40;
	const int SPEED_MAX = 40;
	const int CONVERTER = 10;
	const float PARTICLE_SIZE = 4.f;
	const float TILE_SIZE = 64.f;
public:
	SwordClashParticle(Vector2 pos, Camera2D& ref);
	void Update(float dt) override;
	void Render() override;
};

class SteamParticle : public ParticleEffect
{
private:
	Camera2D* camRef = nullptr;
	const float TIME = 1.5f;
	const static int PARTICLE_NUM = 4;
	Particle particles[PARTICLE_NUM]{ 0.f,0.f,0.f,0.f };
	Vector2 position = { 0.f,0.f };
	//Vector2 velocity = { 0.f,0.f };
	const float BONUS_VELOCITY_REDUCTION = 10.f;

	const float SPEED = -1.f;
	
	const float TILE_SIZE = 64.f;
	const float MIN_SIZE = 8.f;
	const float MAX_SIZE = 32.f;
public:
	SteamParticle(Vector2 pos, Vector2 vel, Camera2D& ref);
	void Update(float dt) override;
	void Render() override;
};