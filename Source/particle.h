#pragma once
#include "raylib.h"

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
	float timeAlive = 0.f;
	bool loop = false;
	bool activated = true;
public:
	virtual void Update(float dt);
	virtual void Render(){};
	void SetTimeAlive(float time) { timeAlive = time; }
	bool IsActivated() { return activated; }
};

class SnowParticle : public ParticleEffect
{
private:
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
	SnowParticle();
	void Update(float dt) override;
	void Render() override;
};

class LeafParticle : public ParticleEffect
{
private:
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
public:
	LeafParticle();
	void Update(float dt) override;
	void Render() override;
};

class SwordClashParticle : public ParticleEffect
{
private:
	Camera2D* camRef = nullptr;
	const float TIME = 2.f;
	const static int PARTICLE_NUM = 20;
	Particle particles[PARTICLE_NUM]{ 0.f,0.f,0.f,0.f };
	Vector2 position = { 0.f,0.f };
public:
	SwordClashParticle(Vector2 pos, Camera2D ref);
	void Update(float dt) override;
	void Render() override;
};