#pragma once
#include "raylib.h"
#include "entity.h"
#include "animation.h"
#include "config.h"
class DartTrap
{
private:
	Entity* playerRef = nullptr;

	Vector2 pos{0.f,0.f};
	Vector2 bulletPos{ 0.f,0.f };

	Animator anim;
	bool active = true;
	float timeAlive = 0.f;
	float speed = 10.f;
	const short int ATTACK_DAMAGE = 10;
	Config config;
	const float FULL_TIME_ALIVE = 3.f;
	const float BULLET_TILE_WIDTH = 2.f;
	const float BULLET_TILE_HEIGHT = 1.f;
	const float BULLET_PIXEL_WIDTH = 32.f;
	const float BULLET_PIXEL_HEIGHT = 16.f;
public:
	~DartTrap();
	void Setup(Vector2 newPos, Entity& ref, bool left);
	void SetTexture(Texture2D txr);
	void Update(float dt); 
	void Render(Rectangle cam);
};